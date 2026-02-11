merge_left_and_right_transloc (Stage3_T *stage3array_sub1, int npaths_sub1, int bestfrom,
			       Stage3_T *stage3array_sub2, int npaths_sub2, int bestto,
			       List_T nonjoinable, int breakpoint, int queryntlength,
#ifdef PMAP
			       char *queryaaseq_ptr,
#endif
			       Sequence_T queryseq, Genome_T genome, Pairpool_T pairpool,
			       int ngap) {
  List_T newstage3list, p;
  Stage3_T best0, best1, *array, last;
  int i, k;

  best0 = stage3array_sub1[bestfrom];
  best1 = stage3array_sub2[bestto];


  debug2(printf("Calling Stage3_merge_chimera with breakpoint %d\n",breakpoint));
  Stage3_merge_chimera(best0,best1,
		       0,breakpoint,
		       breakpoint+1,queryntlength,
#ifdef PMAP
		       queryaaseq_ptr,
#endif
		       queryseq,genome,pairpool,ngap);

  debug2(printf("Rearranging paths\n"));
  newstage3list = (List_T) NULL;
  newstage3list = List_push(newstage3list,(void *) best0);
  newstage3list = List_push(newstage3list,(void *) best1);
  debug2(printf("Pushing stage3 %p\n",best0));
  debug2(printf("Pushing stage3 %p\n",best1));

  if (npaths_sub1 + npaths_sub2 > 2) {


    array = (Stage3_T *) CALLOC(npaths_sub1 + npaths_sub2 - 2,sizeof(Stage3_T));
    k = 0;
    for (i = 0; i < npaths_sub1; i++) {
      if (i != bestfrom) {
	array[k++] = stage3array_sub1[i];
      }
    }
    for (i = 0; i < npaths_sub2; i++) {
      if (i != bestto) {
	array[k++] = stage3array_sub2[i];
      }
    }
    qsort(array,npaths_sub1+npaths_sub2-2,sizeof(Stage3_T),Stage3_identity_cmp);

    last = (Stage3_T) NULL;
    for (i = 0; i < npaths_sub1+npaths_sub2-2; i++) {
      if (array[i] == last) {

	debug2(printf("Skipping stage3 %p, because just pushed\n",array[i]));
      } else if (array[i] == best0 || array[i] == best1) {

	debug2(printf("Skipping stage3 %p, because in chimera\n",array[i]));
      } else {
	debug2(printf("Pushing stage3 %p\n",array[i]));
	newstage3list = List_push(newstage3list,(void *) array[i]);
	last = array[i];
      }
    }

    FREE(array);
  }

  for (p = nonjoinable; p != NULL; p = List_next(p)) {
    debug2(printf("Pushing nonjoinable stage3 %p\n",List_head(p)));
    newstage3list = List_push(newstage3list,(void *) List_head(p));
  }

  return List_reverse(newstage3list);
}
