vectorstrip_free_list(AjPList *list)
{
    AjIList iter;

    iter = ajListIterNewread(*list);
    while(!ajListIterDone(iter))
    {
	EmbPMatMatch fm = ajListIterGet(iter);
	embMatMatchDel(&fm);
    }
    ajListFree(list);
    ajListFree(list);
    ajListIterDel(&iter);

    return;
}
