ajQuerylistTrace(const AjPList list)
{
    AjIList iter;
    AjPQueryList node;
    ajuint i = 0;

    iter = ajListIterNewread(list);

    ajDebug("ajQuerylistTrace %Lu nodes\n", ajListGetLength(list));

    while(!ajListIterDone(iter))
    {
	node = (AjPQueryList) ajListIterGet(iter);
	ajDebug("%3d: '%S' '%S' %d\n",
		++i, node->Qry,
		node->Formatstr, node->Format);
    }

    ajListIterDel(&iter);
    ajDebug("...Done...\n");

    return;
}
