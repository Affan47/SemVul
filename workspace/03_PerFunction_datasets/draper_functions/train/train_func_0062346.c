write_pack_file(git_packbuilder *pb, const char *path)
{
	git_filebuf file = GIT_FILEBUF_INIT;

	if (git_filebuf_open(&file, path, 0) < 0 ||
	    write_pack(pb, &write_pack_to_file, &file) < 0 ||
	    git_filebuf_commit(&file, GIT_PACK_FILE_MODE) < 0) {
		git_filebuf_cleanup(&file);
		return -1;
	}

	return 0;
}
