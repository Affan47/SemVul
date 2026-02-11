addNodes(Agraph_t * g, int hasLabels)
{
    Agnode_t *v;
    Agedge_t *e;
    Agedge_t *ee = NULL;
    Agedge_t **eList = NULL;
    int tempEdgeCnt = 0;
    int id = 0;

    for (v = agfstnode(g); v; v = agnxtnode(g, v)) {
	int type = MND_type(v);
	if (type != STDNODE)
	    continue;
	for (e = agfstout(g, v); e; e = agnxtout(g, e)) {
	    if (MED_type(e) == VIRTUAL)
		continue;
	    eList = RALLOC(tempEdgeCnt + 1, eList, Agedge_t *);
	    eList[tempEdgeCnt] = e;
	    tempEdgeCnt++;
	}
    }
    for (id = 0; id < tempEdgeCnt; id++)
	add_node(g, eList[id], hasLabels);


    for (v = agfstnode(g); v; v = agnxtnode(g, v)) {
	for (e = agfstout(g, v); e; e = agnxtout(g, e)) {
	    if (ee)
		agdelete(g, ee);
	    if (MED_deleteFlag(e) == 1)
		ee = e;
	    else
		ee = NULL;
	}
    }
}
