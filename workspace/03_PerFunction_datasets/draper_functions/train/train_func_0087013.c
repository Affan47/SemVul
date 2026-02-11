pde_subdir_next(struct proc_dir_entry *dir)
{
	return rb_entry_safe(rb_next(&dir->subdir_node), struct proc_dir_entry,
			     subdir_node);
}
