link(const char *oldpath, const char *newpath) {
	int result;
	instw_t instw_o;
	instw_t instw_n;

	REFCOUNT;

	if (!libc_handle)
		initialize();

#if DEBUG
	debug(2,"link(%s,%s)\n",oldpath,newpath);
#endif


	if( !(__instw.gstatus & INSTW_INITIALIZED) ||
	    !(__instw.gstatus & INSTW_OKWRAP) ) {
		result=true_link(oldpath,newpath);
		return result;
	}

	instw_new(&instw_o);
	instw_new(&instw_n);
	instw_setpath(&instw_o,oldpath);
	instw_setpath(&instw_n,newpath);

#if DEBUG
	instw_print(&instw_o);
	instw_print(&instw_n);
#endif

	backup(instw_o.truepath);
	instw_apply(&instw_o);
	instw_apply(&instw_n);

	result=true_link(instw_o.translpath,instw_n.translpath);
	logg("%d\tlink\t%s\t%s\t#%s\n",result,
	    instw_o.reslvpath,instw_n.reslvpath,error(result));

	instw_delete(&instw_o);
	instw_delete(&instw_n);

	return result;
}
