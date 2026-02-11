PORT_LoadLibraryFromOrigin(const char* existingShLibName,
                 PRFuncPtr staticShLibFunc,
                 const char *newShLibName)
{
    PRLibrary *lib = NULL;
    char* fullPath = NULL;
    PRLibSpec libSpec;


    fullPath = PR_GetLibraryFilePathname(existingShLibName,
                                         staticShLibFunc);

    if (fullPath) {
        lib = loader_LoadLibInReferenceDir(fullPath, newShLibName);
#ifdef XP_UNIX
        if (!lib) {


            char* originalfullPath = loader_GetOriginalPathname(fullPath);
            if (originalfullPath) {
                PR_Free(fullPath);
                fullPath = originalfullPath;
                lib = loader_LoadLibInReferenceDir(fullPath, newShLibName);
            }
        }
#endif
        PR_Free(fullPath);
    }
    if (!lib) {
#ifdef DEBUG_LOADER
        PR_fprintf(PR_STDOUT, "\nAttempting to load %s\n", newShLibName);
#endif
        libSpec.type = PR_LibSpec_Pathname;
        libSpec.value.pathname = newShLibName;
        lib = PR_LoadLibraryWithFlags(libSpec, PR_LD_NOW | PR_LD_LOCAL);
    }
    if (NULL == lib) {
#ifdef DEBUG_LOADER
        PR_fprintf(PR_STDOUT, "\nLoading failed : %s.\n", newShLibName);
#endif
    }
    return lib;
}
