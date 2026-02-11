afs_proc_init(void)
{
	_enter("");

	proc_afs = proc_mkdir("fs/afs", NULL);
	if (!proc_afs)
		goto error_dir;

	if (!proc_create("cells", 0644, proc_afs, &afs_proc_cells_fops) ||
	    !proc_create("rootcell", 0644, proc_afs, &afs_proc_rootcell_fops))
		goto error_tree;

	_leave(" = 0");
	return 0;

error_tree:
	remove_proc_subtree("fs/afs", NULL);
error_dir:
	_leave(" = -ENOMEM");
	return -ENOMEM;
}
