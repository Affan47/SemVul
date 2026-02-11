jffs2_del_ino_cache(struct jffs2_sb_info *c, struct jffs2_inode_cache *old)
{
	struct jffs2_inode_cache **prev;

#ifdef CONFIG_JFFS2_FS_XATTR
	BUG_ON(old->xref);
#endif
	dbg_inocache("del %p (ino #%u)\n", old, old->ino);
	spin_lock(&c->inocache_lock);

	prev = &c->inocache_list[old->ino % c->inocache_hashsize];

	while ((*prev) && (*prev)->ino < old->ino) {
		prev = &(*prev)->next;
	}
	if ((*prev) == old) {
		*prev = old->next;
	}


	if (old->state != INO_STATE_READING && old->state != INO_STATE_CLEARING)
		jffs2_free_inode_cache(old);

	spin_unlock(&c->inocache_lock);
}
