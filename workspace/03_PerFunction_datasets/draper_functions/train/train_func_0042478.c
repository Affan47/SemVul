remove_object_files(object_data *d)
{
	if (p_unlink(d->file) < 0) {
		fprintf(stderr, "can't delete object file \"%s\"\n", d->file);
		return -1;
	}
	if ((p_rmdir(d->dir) < 0) && (errno != ENOTEMPTY)) {
		fprintf(stderr, "can't remove directory \"%s\"\n", d->dir);
		return -1;
	}

	if (p_rmdir(odb_dir) < 0) {
		fprintf(stderr, "can't remove directory \"%s\"\n", odb_dir);
		return -1;
	}

	return 0;
}
