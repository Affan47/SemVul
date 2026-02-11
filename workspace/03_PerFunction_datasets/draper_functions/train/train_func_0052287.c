jffs2_obsolete_node_frag(struct jffs2_sb_info *c,
				     struct jffs2_node_frag *this)
{
	if (this->node) {
		this->node->frags--;
		if (!this->node->frags) {

			dbg_fragtree2("marking old node @0x%08x (0x%04x-0x%04x) obsolete\n",
				ref_offset(this->node->raw), this->node->ofs, this->node->ofs+this->node->size);
			jffs2_mark_node_obsolete(c, this->node->raw);
			jffs2_free_full_dnode(this->node);
		} else {
			dbg_fragtree2("marking old node @0x%08x (0x%04x-0x%04x) REF_NORMAL. frags is %d\n",
				ref_offset(this->node->raw), this->node->ofs, this->node->ofs+this->node->size, this->node->frags);
			mark_ref_normal(this->node->raw);
		}

	}
	jffs2_free_node_frag(this);
}
