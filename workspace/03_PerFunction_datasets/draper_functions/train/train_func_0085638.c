cuddUpdateInteractionMatrix(
  DdManager * table,
  int  xindex,
  int  yindex)
{
    int i;
    for (i = 0; i < yindex; i++) {
	if (i != xindex && cuddTestInteract(table,i,yindex)) {
	    if (i < xindex) {
		cuddSetInteract(table,i,xindex);
	    } else {
		cuddSetInteract(table,xindex,i);
	    }
	}
    }
    for (i = yindex+1; i < table->size; i++) {
	if (i != xindex && cuddTestInteract(table,yindex,i)) {
	    if (i < xindex) {
		cuddSetInteract(table,i,xindex);
	    } else {
		cuddSetInteract(table,xindex,i);
	    }
	}
    }

}
