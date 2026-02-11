addMultiplicityGroups(
  DdManager *dd ,
  MtrNode *treenode ,
  int multiplicity ,
  char *vmask ,
  char *lmask )
{
    int startV, stopV, startL;
    int i, j;
    MtrNode *auxnode = treenode;

    while (auxnode != NULL) {
	if (auxnode->child != NULL) {
	    addMultiplicityGroups(dd,auxnode->child,multiplicity,vmask,lmask);
	}

	startV = dd->permZ[auxnode->index] / multiplicity;
	startL = auxnode->low / multiplicity;
	stopV = startV + auxnode->size / multiplicity;

	for (i = startV, j = startL; i < stopV; i++) {
	    if (vmask[i] == 0) {
		MtrNode *node;
		while (lmask[j] == 1) j++;
		node = Mtr_MakeGroup(auxnode, j * multiplicity, multiplicity,
				     MTR_FIXED);
		if (node == NULL) {
		    return(0);
		}
		node->index = dd->invpermZ[i * multiplicity];
		vmask[i] = 1;
		lmask[j] = 1;
	    }
	}
	auxnode = auxnode->younger;
    }
    return(1);

}
