unpartition_filestruct(partition **p)
{
    char *tmp;

    assert(p != NULL && openfile->fileage != NULL && openfile->filebot != NULL);


    tmp = mallocstrcpy(NULL, openfile->fileage->data);
    openfile->fileage->prev = (*p)->top_prev;
    if (openfile->fileage->prev != NULL)
	openfile->fileage->prev->next = openfile->fileage;
    openfile->fileage->data = charealloc(openfile->fileage->data,
	strlen((*p)->top_data) + strlen(openfile->fileage->data) + 1);
    strcpy(openfile->fileage->data, (*p)->top_data);
    free((*p)->top_data);
    strcat(openfile->fileage->data, tmp);
    free(tmp);


    openfile->filebot->next = (*p)->bot_next;
    if (openfile->filebot->next != NULL)
	openfile->filebot->next->prev = openfile->filebot;
    openfile->filebot->data = charealloc(openfile->filebot->data,
	strlen(openfile->filebot->data) + strlen((*p)->bot_data) + 1);
    strcat(openfile->filebot->data, (*p)->bot_data);
    free((*p)->bot_data);


    if ((*p)->fileage != NULL)
	openfile->fileage = (*p)->fileage;
    if ((*p)->filebot != NULL)
	openfile->filebot = (*p)->filebot;


    free(*p);
    *p = NULL;
}
