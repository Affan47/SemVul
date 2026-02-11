branch_close_to_half_and_expensive(lp_prob *p, int max_cand_num,
					int *cand_num, branch_obj ***candidates)
{
   LPdata *lp_data = p->lp_data;
   double *x = lp_data->x;
   double lpetol = lp_data->lpetol, lpetol1 = 1 - lpetol;
   int *xind = lp_data->tmp.i1;
   double fracx, *xval = lp_data->tmp.d;
   branch_obj *cand;
   int i, j, cnt = 0;
   double lim[7] = {.1, .15, .20, .233333, .266667, .3, 1};


   for (i = lp_data->n-1; i >= 0; i--){
      fracx = x[i] - floor(x[i]);
      if (fracx > lpetol && fracx < lpetol1){
	 xind[cnt] = i;
	 xval[cnt++] = fabs(fracx - .5);
       }
   }

   qsort_di(xval, xind, cnt);

   for (j=0, i=0; i<cnt; i++){
      if (xval[i] > lim[j]){
	 if (i == 0){
	    j++; continue;
	 }else{
	    break;
	 }
      }
   }
   cnt = i;

   if (max_cand_num >= cnt){
      *cand_num = cnt;
   }else{
      for (i=cnt-1; i>=0; i--){
	 get_objcoef(p->lp_data, xind[i], xval+i);
	 xval[i] *= -1;
      }
      qsort_di(xval, xind, cnt);
      *cand_num = max_cand_num;
   }

   if (!*candidates)
      *candidates = (branch_obj **) malloc(*cand_num * sizeof(branch_obj *));
   for (i=*cand_num-1; i>=0; i--){
      cand = (*candidates)[i] = (branch_obj *) calloc(1, sizeof(branch_obj) );
      cand->type = CANDIDATE_VARIABLE;
      cand->child_num = 2;
      cand->position = xind[i];
      cand->sense[0] = 'L';
      cand->sense[1] = 'G';
      cand->rhs[0] = floor(x[xind[i]]);
      cand->rhs[1] = cand->rhs[0] + 1;
      cand->range[0] = cand->range[1] = 0;
   }
}
