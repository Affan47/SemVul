follow_symlink( struct pfs_name *pname, int depth )
{
	char link_target[PFS_PATH_MAX];
	char absolute_link_target[PFS_PATH_MAX];
	char *name_to_resolve = link_target;
	struct pfs_name new_pname = *pname;

	int rlres = new_pname.service->readlink(pname,link_target,PFS_PATH_MAX-1);
	if (rlres > 0) {

		link_target[rlres] = '\000';

		if (link_target[0] != '/') {
			 const char *basename_start = string_basename(pname->path);
			 if (basename_start) {
				int dirname_len = basename_start - pname->path;
				snprintf(absolute_link_target,
					PFS_PATH_MAX, "%*.*s%s",
					dirname_len, dirname_len, pname->path,
					link_target);
				name_to_resolve = absolute_link_target;
			}
		}
		if (resolve_name(name_to_resolve, &new_pname, true, depth + 1)) {
			*pname = new_pname;
		}
	}
}
