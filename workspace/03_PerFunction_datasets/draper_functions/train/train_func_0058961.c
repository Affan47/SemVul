saveimagelist_cb(Fl_Object *, void *)
{
    static char currSavePath[100], errmsg[300];
    int         nbitems;
    char *res = mainMenuBar->getItemListContent(IMAGE_LIST_ID, nbitems);

    strcpy(currSavePath, "/usr/tmp/imagelist");

    const char *savePathTxt = fl_input("Enter list save path", currSavePath);

    FILE *saveListFile = fopen(savePathTxt, "w");
    if (saveListFile != NULL) {
	fprintf(saveListFile, "%s", res);
	fclose(saveListFile);
	dbgprintf("Saving %d image names to %s\n", nbitems, savePathTxt);

    } else {
	sprintf(errmsg, "Error saving list to %s\n%s", savePathTxt, strerror(errno));
	fl_alert("%s", errmsg);
    }


    delete[] res;


    return;
}
