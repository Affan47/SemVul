fopensearch(const char* filename, string& fullpath)
{
    FILE* f;
    char* envpath;

    if ((f = fopen(filename, "r"))) {
    	buildFullPathname(fullpath, filename);
    	return f;
    }
    if ((f = fopenat(fullpath, gMasterDirectory, filename))) {
    	return f;
    }
    if ((envpath = getenv("FAUST_LIB_PATH")) && (f = fopenat(fullpath, envpath, filename))) {
		return f;
    }
    if ((f = fopenat(fullpath, gFaustDirectory, "architecture", filename))) {
    	return f;
    }
    if ((f = fopenat(fullpath, gFaustSuperDirectory, "architecture", filename))) {
    	return f;
    }
    if ((f = fopenat(fullpath, gFaustSuperSuperDirectory, "architecture", filename))) {
    	return f;
    }
#ifdef INSTALL_PREFIX
    if ((f = fopenat(fullpath, INSTALL_PREFIX "/lib/faust", filename))) {
    	return f;
    }
#endif
    if ((f = fopenat(fullpath, "/usr/local/lib/faust", filename))) {
    	return f;
    }
    if ((f = fopenat(fullpath, "/usr/lib/faust", filename))) {
    	return f;
    }
    return 0;
}
