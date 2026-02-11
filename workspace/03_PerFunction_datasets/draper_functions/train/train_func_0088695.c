dereference3(DCEconstraint* constraint)
{
    int i;
    NClist* allnodes = dceallnodes((DCEnode*)constraint,CES_NIL);
    for(i=0;i<nclistlength(allnodes);i++) {
	DCEnode* node = (DCEnode*)nclistget(allnodes,i);
	switch(node->sort) {
	case CES_SEGMENT:
	    ((DCEsegment*)node)->cdfnode = NULL;
	    break;
	case CES_VAR:
	    ((DCEvar*)node)->cdfnode = NULL;
	    ((DCEvar*)node)->cdfleaf = NULL;
	    break;
	default: break;
	}
    }
    nclistfree(allnodes);
}
