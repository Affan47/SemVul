BuildFileList (ml_state_t *msp, const char *bootlist, int *mbplp)
{
    FILE	*listF;
    ml_val_t	*fileNames = NULL;
    char	*nameBuf = NULL;
    int         max_num_boot_files = MAX_NUM_BOOT_FILES;
    int         max_boot_path_len = MAX_BOOT_PATH_LEN;
    int		i, j, numFiles;
    ml_val_t	fileList;
# define SIZE_BUF_LEN	128
    char        sizeBuf[SIZE_BUF_LEN];
    char        c;

    numFiles = 0;

    listF = OpenBinFile (bootlist, FALSE);

    if (listF != NULL) {
	c = getc (listF);
	if (c == EOF)
	    Die ("bootlist file \"%s\" is empty", bootlist);
	if (c == '%') {
	    if (fgets (sizeBuf, SIZE_BUF_LEN, listF) != NIL(char *)) {

		char *space = strchr (sizeBuf, ' ');
		*space = '\0';
		max_num_boot_files = strtoul(sizeBuf, NULL, 0);
		max_boot_path_len = strtoul(space+1, NULL, 0) + 2;
	    }
	    else
		Die ("unable to read first line in \"%s\" after %%", bootlist);
	}
	else {

	    ungetc (c, listF);
	}

	*mbplp = max_boot_path_len;

	if ((nameBuf = MALLOC(max_boot_path_len)) == NIL(char *))
	    Die ("unable to allocate space for boot file names");

	if ((fileNames = MALLOC(max_num_boot_files * sizeof(char *))) == NULL)
	    Die ("unable to allocate space for boot file name table");


	while (fgets (nameBuf, max_boot_path_len, listF) != NIL(char *)) {
	    j = strlen(nameBuf)-1;
	    if (nameBuf[j] == '\n') nameBuf[j] = '\0';
	    if (numFiles < max_num_boot_files)
		fileNames[numFiles++] = ML_CString(msp, nameBuf);
	    else
		Die ("too many files\n");
	}
	fclose (listF);
    }


    for (fileList = LIST_nil, i = numFiles;  --i >= 0; ) {
	LIST_cons(msp, fileList, fileNames[i], fileList);
    }


    if (fileNames)
	FREE (fileNames);
    if (nameBuf)
	FREE (nameBuf);

    return fileList;

}
