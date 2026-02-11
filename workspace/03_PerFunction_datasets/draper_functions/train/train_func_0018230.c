add_packed_git(const char *path, int path_len, int local)
{
	struct stat st;
	struct packed_git *p = alloc_packed_git(path_len + 2);


	path_len -= strlen(".idx");
	if (path_len < 1) {
		free(p);
		return NULL;
	}
	memcpy(p->pack_name, path, path_len);

	strcpy(p->pack_name + path_len, ".keep");
	if (!access(p->pack_name, F_OK))
		p->pack_keep = 1;

	strcpy(p->pack_name + path_len, ".pack");
	if (stat(p->pack_name, &st) || !S_ISREG(st.st_mode)) {
		free(p);
		return NULL;
	}


	p->pack_size = st.st_size;
	p->pack_local = local;
	p->mtime = st.st_mtime;
	if (path_len < 40 || get_sha1_hex(path + path_len - 40, p->sha1))
		hashclr(p->sha1);
	return p;
}
