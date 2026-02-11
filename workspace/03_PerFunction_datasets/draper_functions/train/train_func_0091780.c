no_overlapping_node(struct jffs2_sb_info *c, struct rb_root *root,
		 	       struct jffs2_node_frag *newfrag,
			       struct jffs2_node_frag *this, uint32_t lastend)
{
	if (lastend < newfrag->node->ofs) {

		struct jffs2_node_frag *holefrag;

		holefrag= new_fragment(NULL, lastend, newfrag->node->ofs - lastend);
		if (unlikely(!holefrag)) {
			jffs2_free_node_frag(newfrag);
			return -ENOMEM;
		}

		if (this) {


			dbg_fragtree2("add hole frag %#04x-%#04x on the right of the new frag.\n",
				holefrag->ofs, holefrag->ofs + holefrag->size);
			rb_link_node(&holefrag->rb, &this->rb, &this->rb.rb_right);
		} else {
			dbg_fragtree2("Add hole frag %#04x-%#04x to the root of the tree.\n",
				holefrag->ofs, holefrag->ofs + holefrag->size);
			rb_link_node(&holefrag->rb, NULL, &root->rb_node);
		}
		rb_insert_color(&holefrag->rb, root);
		this = holefrag;
	}

	if (this) {


		dbg_fragtree2("add the new node at the right\n");
		rb_link_node(&newfrag->rb, &this->rb, &this->rb.rb_right);
	} else {
		dbg_fragtree2("insert the new node at the root of the tree\n");
		rb_link_node(&newfrag->rb, NULL, &root->rb_node);
	}
	rb_insert_color(&newfrag->rb, root);

	return 0;
}
