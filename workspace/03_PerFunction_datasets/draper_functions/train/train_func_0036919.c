Gregion_sort_low_descending (List_T gregions) {
  List_T sorted = NULL;
  Gregion_T *array;
  int n, i;

  if ((n = List_length(gregions)) == 0) {
    return (List_T) NULL;
  } else {
    array = (Gregion_T *) List_to_array(gregions,NULL);
    qsort(array,n,sizeof(Gregion_T),Gregion_low_descending_cmp);

    for (i = n-1; i >= 0; i--) {
      sorted = List_push(sorted,array[i]);
    }
    FREE(array);
    return sorted;
  }
}
