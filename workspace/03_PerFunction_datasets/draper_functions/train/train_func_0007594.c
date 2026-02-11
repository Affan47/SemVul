sp_add_solution (lp_prob *p, int cnt, int *indices, double *values,
      double obj_value, int bc_index)
{
   sp_desc *sp = p->tm->sp;
   sp_solution *sol;


   if (sp->num_solutions == sp->max_solutions &&
         sp->solutions[0]->objval>=obj_value+p->lp_data->lpetol) {

      sp_delete_solution(sp,0);


   } else if (sp->num_solutions == sp->max_solutions) {


      return 0;
   }
   sol = sp->solutions[sp->num_solutions];
   sol->objval = obj_value;
   sol->xlength = cnt;
   sol->xind = (int *) malloc(ISIZE*cnt);
   memcpy(sol->xind,indices,ISIZE*cnt);
   sol->xval = (double *) malloc(DSIZE*cnt);
   memcpy(sol->xval,values,DSIZE*cnt);
   sol->node_index = bc_index;
   sp->num_solutions++;
   sp->total_num_sols_found++;
   PRINT(p->par.verbosity,5,("sp: solution pool size = %d \n",
            sp->num_solutions));
   return 0;
}
