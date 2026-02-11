au_do_flush_nondir(struct file *file, fl_owner_t id)
{
	int err;
	struct file *h_file;

	err = 0;
	h_file = au_hf_top(file);
	if (h_file)
		err = vfsub_flush(h_file, id);
	return err;
}
