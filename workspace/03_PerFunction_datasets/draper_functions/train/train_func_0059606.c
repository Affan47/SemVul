free_candidate(branch_obj **cand)
{
   int i;

   if (*cand){
      branch_obj *can = *cand;
#ifdef COMPILE_FRAC_BRANCHING
      for (i = can->child_num-1; i >= 0; i--){
	 if (can->frac_num[i]){
	    FREE(can->frac_ind[i]);
	    FREE(can->frac_val[i]);
	 }
      }
#endif
      free_waiting_row(&(can->row));
#ifndef MAX_CHILDREN_NUM
      FREE(can->sense); FREE(can->rhs); FREE(can->range); FREE(can->branch);

      if (can->solutions){
	 for (i = can->child_num-1; i >= 0; i--){
#else
      if (can->solutions){
         for (i = MAX_CHILDREN_NUM - 1; i >= 0; i--){
#endif
	    FREE(can->sol_inds[i]);
	    FREE(can->solutions[i]);
	 }
      }

#ifdef SENSITIVITY_ANALYSIS
#ifndef MAX_CHILDREN_NUM
      if (can->duals){
	 for (i = can->child_num-1; i >= 0; i--){
#else
      if (can->duals){
	 for (i = MAX_CHILDREN_NUM - 1; i >= 0; i--){
#endif
	    FREE(can->duals[i]);
	 }
      }
#endif

      FREE(can->sol_sizes);
      FREE(can->sol_inds);
      FREE(can->solutions);
#ifdef SENSITIVITY_ANALYSIS
      FREE(can->duals);
#endif

      FREE(*cand);
   }
}
