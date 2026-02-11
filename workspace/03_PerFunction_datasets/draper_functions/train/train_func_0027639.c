grow_dirent_lookup_recursive( const char *path, struct grow_dirent *root, int link_count )
{
	struct grow_dirent *d;

	if(!path) path = "\0";
	while(*path=='/') path++;

	if( S_ISLNK(root->mode) && ( link_count>0 || path[0] ) ) {
		if(link_count>100) {
			errno = ELOOP;
			return 0;
		}

		char *linkname = root->linkname;

		if(linkname[0]=='/') {
			while(root->parent) {
				root = root->parent;
			}
		} else {
			root = root->parent;
		}

		root = grow_dirent_lookup_recursive(linkname,root,link_count+1);
		if(!root) {
			errno = ENOENT;
			return 0;
		}
	}

	if(!*path) return root;

	if(!S_ISDIR(root->mode)) {
		errno = ENOTDIR;
		return 0;
	}

	const char *subpath = strchr(path,'/');
	if(!subpath) subpath = "\0";

	if(compare_path_element(".",path)) {
		return grow_dirent_lookup_recursive(subpath,root,link_count);
	}

	if(compare_path_element("..",path)) {
		if(root->parent) {
			return grow_dirent_lookup_recursive(subpath,root->parent,link_count);
		} else {
			errno = ENOENT;
			return 0;
		}
	}

	for(d=root->children;d;d=d->next) {
		if(compare_path_element(d->name,path)) {
			return grow_dirent_lookup_recursive(subpath,d,link_count);
		}
	}

	errno = ENOENT;
	return 0;
}
