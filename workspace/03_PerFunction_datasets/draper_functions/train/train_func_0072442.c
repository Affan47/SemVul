__add_cap_flushing_to_inode(struct ceph_inode_info *ci,
					struct ceph_cap_flush *cf)
{
	struct rb_node **p = &ci->i_cap_flush_tree.rb_node;
	struct rb_node *parent = NULL;
	struct ceph_cap_flush *other = NULL;

	while (*p) {
		parent = *p;
		other = rb_entry(parent, struct ceph_cap_flush, i_node);

		if (cf->tid < other->tid)
			p = &(*p)->rb_left;
		else if (cf->tid > other->tid)
			p = &(*p)->rb_right;
		else
			BUG();
	}

	rb_link_node(&cf->i_node, parent, p);
	rb_insert_color(&cf->i_node, &ci->i_cap_flush_tree);
}
