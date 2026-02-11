au_do_aopen(struct inode *inode, struct file *file)
{
	struct au_sphlhead *aopen;
	struct aopen_node *node;
	struct au_do_open_args args = {
		.no_lock	= 1,
		.open		= au_do_open_nondir
	};

	aopen = &au_sbi(inode->i_sb)->si_aopen;
	spin_lock(&aopen->spin);
	hlist_for_each_entry(node, &aopen->head, hlist)
		if (node->file == file) {
			args.h_file = node->h_file;
			break;
		}
	spin_unlock(&aopen->spin);


	return au_do_open(file, &args);
}
