send_cg_data_u(sym_environment *env, int sender)
{
#if defined(COMPILE_IN_TM) && defined(COMPILE_IN_LP) && defined(COMPILE_IN_CG)
   int i;
   tm_prob *tm = env->tm;
   tm->cgp = (cg_prob **) malloc(tm->par.max_active_nodes*sizeof(cg_prob *));
#pragma omp parallel for
   for (i = 0; i < tm->par.max_active_nodes; i++){
      tm->lpp[i]->cgp = tm->cgp[i] = (cg_prob *) calloc(1, sizeof(cg_prob));

      tm->cgp[i]->par = env->par.cg_par;

      tm->cgp[i]->draw_graph = env->dg_tid;
   }
#ifdef USE_SYM_APPLICATION
   for (i = 0; i < tm->par.max_active_nodes; i++){
      CALL_USER_FUNCTION( user_send_cg_data(env->user,
					    &(tm->lpp[i]->cgp->user)) );
   }
#endif
#else
   int s_bufid;

   s_bufid = init_send(DataInPlace);
   send_char_array((char *)(&env->par.cg_par), sizeof(cg_params));
   send_int_array(&env->dg_tid, 1);
#ifdef USE_SYM_APPLICATION
   CALL_USER_FUNCTION( user_send_cg_data(env->user, NULL) );
#endif
   send_msg(sender, CG_DATA);
   freebuf(s_bufid);
#endif

   return(FUNCTION_TERMINATED_NORMALLY);
}
