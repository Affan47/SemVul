help(
    char *keyword,
    char *path,
    TBOOLEAN *subtopics)

{
    static char oldpath[PATHSIZE] = "";
    int status;
    KEY *key;


    errno = 0;
    if (strncmp(oldpath, path, PATHSIZE) != 0)
	FreeHelp();
    if (keys == NULL) {
	status = LoadHelp(path);
	if (status == H_ERROR)
	    return (status);


	safe_strncpy(oldpath, path, PATHSIZE);
    }

    key = FindHelp(keyword);
    if (key != NULL) {

	if (key->text)
	    PrintHelp(key, subtopics);
	status = H_FOUND;
    } else {
	status = H_NOTFOUND;
    }

    return (status);
}
