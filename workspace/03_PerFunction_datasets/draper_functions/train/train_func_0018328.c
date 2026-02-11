jffs2_add_physical_node_ref(struct jffs2_sb_info *c,
						       uint32_t ofs, uint32_t len,
						       struct jffs2_inode_cache *ic)
{
	struct jffs2_eraseblock *jeb;
	struct jffs2_raw_node_ref *new;

	jeb = &c->blocks[ofs / c->sector_size];

	jffs2_dbg(1, "%s(): Node at 0x%x(%d), size 0x%x\n",
		  __func__, ofs & ~3, ofs & 3, len);
#if 1


	if ((c->nextblock || ((ofs & 3) != REF_OBSOLETE))
	    && (jeb != c->nextblock || (ofs & ~3) != jeb->offset + (c->sector_size - jeb->free_size))) {
		pr_warn("argh. node added in wrong place at 0x%08x(%d)\n",
			ofs & ~3, ofs & 3);
		if (c->nextblock)
			pr_warn("nextblock 0x%08x", c->nextblock->offset);
		else
			pr_warn("No nextblock");
		pr_cont(", expected at %08x\n",
			jeb->offset + (c->sector_size - jeb->free_size));
		return ERR_PTR(-EINVAL);
	}
#endif
	spin_lock(&c->erase_completion_lock);

	new = jffs2_link_node_ref(c, jeb, ofs, len, ic);

	if (!jeb->free_size && !jeb->dirty_size && !ISDIRTY(jeb->wasted_size)) {

		jffs2_dbg(1, "Adding full erase block at 0x%08x to clean_list (free 0x%08x, dirty 0x%08x, used 0x%08x\n",
			  jeb->offset, jeb->free_size, jeb->dirty_size,
			  jeb->used_size);
		if (jffs2_wbuf_dirty(c)) {

			spin_unlock(&c->erase_completion_lock);
			jffs2_flush_wbuf_pad(c);
			spin_lock(&c->erase_completion_lock);
		}

		list_add_tail(&jeb->list, &c->clean_list);
		c->nextblock = NULL;
	}
	jffs2_dbg_acct_sanity_check_nolock(c,jeb);
	jffs2_dbg_acct_paranoia_check_nolock(c, jeb);

	spin_unlock(&c->erase_completion_lock);

	return new;
}
