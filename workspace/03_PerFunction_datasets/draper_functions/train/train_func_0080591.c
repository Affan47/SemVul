ubifs_add_nnode_dirt(struct ubifs_info *c, struct ubifs_nnode *nnode)
{
	struct ubifs_nnode *np = nnode->parent;

	if (np)
		ubifs_add_lpt_dirt(c, np->nbranch[nnode->iip].lnum,
				   c->nnode_sz);
	else {
		ubifs_add_lpt_dirt(c, c->lpt_lnum, c->nnode_sz);
		if (!(c->lpt_drty_flgs & LTAB_DIRTY)) {
			c->lpt_drty_flgs |= LTAB_DIRTY;
			ubifs_add_lpt_dirt(c, c->ltab_lnum, c->ltab_sz);
		}
	}
}
