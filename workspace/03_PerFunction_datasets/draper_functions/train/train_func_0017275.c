proc_remove(struct proc_dir_entry *de)
{
	if (de)
		remove_proc_subtree(de->name, de->parent);
}
