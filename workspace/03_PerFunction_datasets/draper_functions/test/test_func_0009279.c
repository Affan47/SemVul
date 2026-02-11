sp_free_sp(sp_desc *sp)
{
   int i;


   for (i=sp->num_solutions-1; i>=0; i--) {
      sp_delete_solution(sp,i);
   }
   for (i=sp->max_solutions-1; i>-1; i--) {
      FREE(sp->solutions[i]);
   }
   FREE(sp->solutions);
   return 0;
}
