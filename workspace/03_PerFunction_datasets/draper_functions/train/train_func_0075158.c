jffs2_block_refile(struct jffs2_sb_info *c, struct jffs2_eraseblock *jeb, int allow_empty)
{
	jffs2_dbg(1, "About to refile bad block at %08x\n", jeb->offset);


	if (c->nextblock == jeb)
		c->nextblock = NULL;
	else
		list_del(&jeb->list);
	if (jeb->first_node) {
		jffs2_dbg(1, "Refiling block at %08x to bad_used_list\n",
			  jeb->offset);
		list_add(&jeb->list, &c->bad_used_list);
	} else {
		BUG_ON(allow_empty == REFILE_NOTEMPTY);

		jffs2_dbg(1, "Refiling block at %08x to erase_pending_list\n",
			  jeb->offset);
		list_add(&jeb->list, &c->erase_pending_list);
		c->nr_erasing_blocks++;
		jffs2_garbage_collect_trigger(c);
	}

	if (!jffs2_prealloc_raw_node_refs(c, jeb, 1)) {
		uint32_t oldfree = jeb->free_size;

		jffs2_link_node_ref(c, jeb,
				    (jeb->offset+c->sector_size-oldfree) | REF_OBSOLETE,
				    oldfree, NULL);

		c->wasted_size += oldfree;
		jeb->wasted_size += oldfree;
		c->dirty_size -= oldfree;
		jeb->dirty_size -= oldfree;
	}

	jffs2_dbg_dump_block_lists_nolock(c);
	jffs2_dbg_acct_sanity_check_nolock(c,jeb);
	jffs2_dbg_acct_paranoia_check_nolock(c, jeb);
}
