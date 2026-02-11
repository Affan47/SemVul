try_get_path2(struct fuse *f, fuse_ino_t nodeid1, const char *name1,
			 fuse_ino_t nodeid2, const char *name2,
			 char **path1, char **path2,
			 struct node **wnode1, struct node **wnode2)
{
	int err;


	err = try_get_path(f, nodeid1, name1, path1, wnode1, true);
	if (!err) {
		err = try_get_path(f, nodeid2, name2, path2, wnode2, true);
		if (err) {
			struct node *wn1 = wnode1 ? *wnode1 : NULL;

			unlock_path(f, nodeid1, wn1, NULL);
			free(*path1);
		}
	}
	return err;
}
