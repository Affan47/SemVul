__fxstatat (int version, int dirfd, const char *path, struct stat *s, int flags) {

 	int result;
 	instw_t instw;


         if(dirfd == AT_FDCWD || *path == '/')
		{
		 #if DEBUG
			debug(2, "__fxstatat(%d,%s,%p,0%o)\n", dirfd, path, s, flags);
		 #endif


		 if ( flags & AT_SYMLINK_NOFOLLOW ) {
		    return __lxstat(version, path, s);
		 }
		 else {
		    return __xstat(version, path, s);
		 }

		}

 	REFCOUNT;

 	if (!libc_handle)
 		initialize();

#if DEBUG
	debug(2, "__fxstatat(%d,%s,%p,0%o)\n", dirfd, path, s, flags);
#endif


 	if(!(__instw.gstatus & INSTW_INITIALIZED) ||
 	   !(__instw.gstatus & INSTW_OKWRAP)) {


		 if ( flags & AT_SYMLINK_NOFOLLOW ) {
		    return true_lxstat(version, path, s);
		 }
		 else {
 		    return true_xstat(version, path, s);
		 }
	}


 	instw_new(&instw);
 	instw_setpathrel(&instw,dirfd,path);

#if DEBUG
 	instw_print(&instw);
#endif


		 if ( flags & AT_SYMLINK_NOFOLLOW ) {
 		    result=__lxstat(version, instw.path, s);
		 }
		 else {
 		    result=__xstat(version, instw.path, s);

		 }

 	instw_delete(&instw);

	return result;
}
