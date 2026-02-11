cg_add_user_cut(cut_data *new_cut, int *num_cuts, int *alloc_cuts,
		    cut_data ***cuts)
{
#ifdef COMPILE_IN_CG

   int i;
   cut_data *tmp_cut;

   for (i = 0; i < *num_cuts; i++){
      if (new_cut->size != (*cuts)[i]->size){
	 continue;
      }
      if (memcmp(new_cut->coef, (*cuts)[i]->coef, new_cut->size) == 0){
	 return(0);
      }
   }
   if (new_cut->name != CUT__DO_NOT_SEND_TO_CP)
      new_cut->name = CUT__SEND_TO_CP;
   tmp_cut = (cut_data *) malloc (sizeof(cut_data));
   memcpy((char *)tmp_cut, (char *)new_cut, sizeof(cut_data));
   if (new_cut->size >0){
      tmp_cut->coef = (char *) malloc (new_cut->size * sizeof(char));
      memcpy((char *)tmp_cut->coef, (char *)new_cut->coef,
	     new_cut->size * sizeof(char));
   }
   REALLOC((*cuts), cut_data *, (*alloc_cuts), (*num_cuts + 1), BB_BUNCH);
   (*cuts)[(*num_cuts)++] = tmp_cut;

#else

   int s_bufid;

   if (new_cut->name != CUT__DO_NOT_SEND_TO_CP)
      new_cut->name = CUT__SEND_TO_CP;
   s_bufid = init_send(DataInPlace);
   pack_cut(new_cut);
   send_msg(p->cur_sol.lp, PACKED_CUT);
   freebuf(s_bufid);

#endif

   return(1);
}
