free_master_u(sym_environment *env)
{
   int i;

#ifdef USE_SYM_APPLICATION
   CALL_USER_FUNCTION( user_free_master(&env->user) );
#endif
   FREE(env->best_sol.xind);
   FREE(env->best_sol.xval);

   if (env->mip){
      free_mip_desc(env->mip);
      FREE(env->mip);
   }

   if(env->prep_mip){
      free_mip_desc(env->prep_mip);
      FREE(env->prep_mip);
   }

   if (env->rootdesc){
      FREE(env->rootdesc->desc);
      FREE(env->rootdesc->uind.list);
      FREE(env->rootdesc->not_fixed.list);
      FREE(env->rootdesc->cutind.list);
      FREE(env->rootdesc);
   }

   if (env->base){
      FREE(env->base->userind);
      FREE(env->base);
   }

#ifdef COMPILE_IN_TM
   if (env->warm_start){
      free_subtree(env->warm_start->rootnode);
      if(env->warm_start->best_sol.has_sol){
	 FREE(env->warm_start->best_sol.xind);
	 FREE(env->warm_start->best_sol.xval);
      }
      if (env->warm_start->cuts){
	 for (i = env->warm_start->cut_num - 1; i >= 0; i--){
	    if (env->warm_start->cuts[i]){
	       FREE(env->warm_start->cuts[i]->coef);
	    }
	    FREE(env->warm_start->cuts[i]);
	 }
      }

      FREE(env->warm_start->cuts);
      FREE(env->warm_start);
   }
#ifdef COMPILE_IN_CP
   if (env->cp){
      for (i = 0; i < env->par.tm_par.max_cp_num; i++){
	 env->cp[i]->msgtag = YOU_CAN_DIE;
	 cp_close(env->cp[i]);
      }
      FREE(env->cp);
   }
#endif
#endif

   return(FUNCTION_TERMINATED_NORMALLY);
}
