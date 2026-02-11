free_mcLevel (mcLevel* l)
{
    int i;

    for (i = 0; i < l->nodecnt; i++)
	free_mcNode (l->nodes[i]);
    l->nodecnt++;
    free (l->nodes);
    free (l);
}
