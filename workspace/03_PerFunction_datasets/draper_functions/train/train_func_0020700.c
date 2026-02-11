pde_subdir_insert(struct proc_dir_entry *dir,
			      struct proc_dir_entry *de)
{
	struct rb_root *root = &dir->subdir;
	struct rb_node **new = &root->rb_node, *parent = NULL;


	while (*new) {
		struct proc_dir_entry *this =
			container_of(*new, struct proc_dir_entry, subdir_node);
		int result = proc_match(de->namelen, de->name, this);

		parent = *new;
		if (result < 0)
			new = &(*new)->rb_left;
		else if (result > 0)
			new = &(*new)->rb_right;
		else
			return false;
	}


	rb_link_node(&de->subdir_node, parent, new);
	rb_insert_color(&de->subdir_node, root);
	return true;
}
