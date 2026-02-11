gli_new_fileref(char *filename, glui32 usage, glui32 rock)
{
    fileref_t *fref = (fileref_t *)malloc(sizeof(fileref_t));
    if (!fref)
        return NULL;

    fref->magicnum = MAGIC_FILEREF_NUM;
    fref->rock = rock;

    fref->filename = malloc(1 + strlen(filename));
    strcpy(fref->filename, filename);

    fref->textmode = ((usage & fileusage_TextMode) != 0);
    fref->filetype = (usage & fileusage_TypeMask);

    fref->prev = NULL;
    fref->next = gli_filereflist;
    gli_filereflist = fref;
    if (fref->next)
        fref->next->prev = fref;

    if (gli_register_obj)
        fref->disprock = (*gli_register_obj)(fref, gidisp_Class_Fileref);
    else
        fref->disprock.ptr = NULL;

    return fref;
}
