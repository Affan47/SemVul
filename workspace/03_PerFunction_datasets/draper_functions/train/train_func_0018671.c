dblayer_get_region_size(const char *dir)
{
    PRFileInfo64 info;
    PRDir *dirhandle = NULL;
    PRDirEntry *direntry = NULL;
    PRUint64 region_size = 0;

    dirhandle = PR_OpenDir(dir);
    if (NULL == dirhandle){
        return region_size;
    }
    while (NULL != (direntry = PR_ReadDir(dirhandle, PR_SKIP_DOT | PR_SKIP_DOT_DOT))){
        if (NULL == direntry->name){
            continue;
        }
        if (0 == strncmp(direntry->name, DB_REGION_PREFIX, 5)){
            char filename[MAXPATHLEN];

            PR_snprintf(filename, MAXPATHLEN, "%s/%s", dir, direntry->name);
            if (PR_GetFileInfo64(filename, &info) != PR_FAILURE){
                region_size += info.size;
    	    }
        }
    }
    PR_CloseDir(dirhandle);

    return region_size;
}
