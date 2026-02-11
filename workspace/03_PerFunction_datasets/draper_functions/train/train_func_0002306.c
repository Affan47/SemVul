tree_dir_next_posix(struct tree *t)
{
	int r;
	const char *name;
	size_t namelen;

	if (t->d == NULL) {
#if defined(HAVE_READDIR_R)
		size_t dirent_size;
#endif

#if defined(HAVE_FDOPENDIR)
		t->d = fdopendir(tree_dup(t->working_dir_fd));
#else
		if (tree_enter_working_dir(t) == 0) {
			t->d = opendir(".");
#if HAVE_DIRFD || defined(dirfd)
			__archive_ensure_cloexec_flag(dirfd(t->d));
#endif
		}
#endif
		if (t->d == NULL) {
			r = tree_ascend(t);
			tree_pop(t);
			t->tree_errno = errno;
			t->visit_type = r != 0 ? r : TREE_ERROR_DIR;
			return (t->visit_type);
		}
#if defined(HAVE_READDIR_R)
		dirent_size = offsetof(struct dirent, d_name) +
		  t->filesystem_table[t->current->filesystem_id].name_max + 1;
		if (t->dirent == NULL || t->dirent_allocated < dirent_size) {
			free(t->dirent);
			t->dirent = malloc(dirent_size);
			if (t->dirent == NULL) {
				closedir(t->d);
				t->d = INVALID_DIR_HANDLE;
				(void)tree_ascend(t);
				tree_pop(t);
				t->tree_errno = ENOMEM;
				t->visit_type = TREE_ERROR_DIR;
				return (t->visit_type);
			}
			t->dirent_allocated = dirent_size;
		}
#endif
	}
	for (;;) {
		errno = 0;
#if defined(HAVE_READDIR_R)
		r = readdir_r(t->d, t->dirent, &t->de);
#ifdef _AIX


		if (r == 9)
			r = errno;
#endif
		if (r != 0 || t->de == NULL) {
#else
		t->de = readdir(t->d);
		if (t->de == NULL) {
			r = errno;
#endif
			closedir(t->d);
			t->d = INVALID_DIR_HANDLE;
			if (r != 0) {
				t->tree_errno = r;
				t->visit_type = TREE_ERROR_DIR;
				return (t->visit_type);
			} else
				return (0);
		}
		name = t->de->d_name;
		namelen = D_NAMELEN(t->de);
		t->flags &= ~hasLstat;
		t->flags &= ~hasStat;
		if (name[0] == '.' && name[1] == '\0')
			continue;
		if (name[0] == '.' && name[1] == '.' && name[2] == '\0')
			continue;
		tree_append(t, name, namelen);
		return (t->visit_type = TREE_REGULAR);
	}
}
