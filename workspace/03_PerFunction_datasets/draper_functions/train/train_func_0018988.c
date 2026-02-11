sftkdb_LoadLibrary(const char *libname)
{
    PRLibrary *lib = NULL;
    PRFuncPtr fn_addr;
    char *parentLibPath = NULL;

    fn_addr  = (PRFuncPtr) &sftkdb_LoadLibrary;
    parentLibPath = PR_GetLibraryFilePathname(SOFTOKEN_LIB_NAME, fn_addr);

    if (!parentLibPath) {
	goto done;
    }

    lib = sftkdb_LoadFromPath(parentLibPath, libname);
#ifdef XP_UNIX

    if (!lib) {
	char *trueParentLibPath = sftkdb_resolvePath(parentLibPath);
	if (!trueParentLibPath) {
	    goto done;
	}
    	lib = sftkdb_LoadFromPath(trueParentLibPath, libname);
	PORT_Free(trueParentLibPath);
    }
#endif

done:
    if (parentLibPath) {
	PORT_Free(parentLibPath);
    }


    if (!lib) {
	PRLibSpec libSpec;
	libSpec.type = PR_LibSpec_Pathname;
	libSpec.value.pathname = libname;
	lib = PR_LoadLibraryWithFlags(libSpec, PR_LD_NOW | PR_LD_LOCAL);
    }

    return lib;
}
