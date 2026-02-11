cmp_action_list(const qsort_t *a1, const qsort_t *a2)
{
    ACTION_LIST_S *x = (ACTION_LIST_S *)a1;
    ACTION_LIST_S *y = (ACTION_LIST_S *)a2;

    if(x->pab != y->pab)
      return((x->pab > y->pab) ? 1 : -1);


    if(x->dup){
	if(y->dup)
	  return((x->num_in_dst > y->num_in_dst) ? -1
		   : (x->num_in_dst == y->num_in_dst) ? 0 : 1);
	else
	  return(-1);
    }
    else if(y->dup)
      return(1);
    else
      return((x->num > y->num) ? -1 : (x->num == y->num) ? 0 : 1);
}
