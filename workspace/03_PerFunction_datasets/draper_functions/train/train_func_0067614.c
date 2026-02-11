merge_double_array_descs(double_array_desc *dad,
			      double_array_desc *moddad)
{
   if (moddad->size != 0){
      if (dad->size == 0){
	 *dad = *moddad;
#ifdef COMPILE_IN_LP
      moddad->stat = moddad->list = NULL;
#endif
      }else{
	 int i, j, k;
	 int  oldsize = dad->size;
	 int *oldlist = dad->list;
	 int *oldstat = dad->stat;
	 int newsize = moddad->size;
	 int *newlist = moddad->list;
	 int *newstat = moddad->stat;
	 int *dlist = dad->list = (int *) malloc((oldsize+newsize) * ISIZE);
	 int *dstat = dad->stat = (int *) malloc((oldsize+newsize) * ISIZE);

	 for (k = 0, i = j = 0; i < oldsize && j < newsize; ){
	    if (oldlist[i] < newlist[j]){
	       dlist[k] = oldlist[i];
	       dstat[k++] = oldstat[i++];
	    }else{
	       if (oldlist[i] == newlist[j])
		  i++;
	       dlist[k] = newlist[j];
	       dstat[k++] = newstat[j++];
	    }
	 }
	 while (i < oldsize){
	    dlist[k] = oldlist[i];
	    dstat[k++] = oldstat[i++];
	 }
	 while (j < newsize){
	    dlist[k] = newlist[j];
	    dstat[k++] = newstat[j++];
	 }
	 dad->size = k;
	 FREE(oldlist);
	 FREE(oldstat);
	 FREE(moddad->list);
	 FREE(moddad->stat);
      }
   }
}
