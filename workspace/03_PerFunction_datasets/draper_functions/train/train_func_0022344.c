receive_feasible_solution_u(sym_environment *env, int msgtag)
{
   receive_int_array(&(env->best_sol.xlevel), 1);
   receive_int_array(&(env->best_sol.xindex), 1);
   receive_int_array(&(env->best_sol.xiter_num), 1);
   receive_dbl_array(&(env->best_sol.lpetol), 1);
   receive_dbl_array(&(env->best_sol.objval), 1);
   receive_int_array(&(env->best_sol.xlength), 1);
   if (env->best_sol.xlength > 0){
      FREE(env->best_sol.xind);
      FREE(env->best_sol.xval);
      env->best_sol.xind = (int *) malloc(env->best_sol.xlength * ISIZE);
      env->best_sol.xval = (double *) malloc(env->best_sol.xlength * DSIZE);
      receive_int_array(env->best_sol.xind, env->best_sol.xlength);
      receive_dbl_array(env->best_sol.xval, env->best_sol.xlength);
   }
   if (!env->has_ub || env->best_sol.objval < env->ub){
      env->has_ub = TRUE;
      env->ub = env->best_sol.objval;
   }
   env->best_sol.has_sol = TRUE;

   switch (msgtag){
    case FEASIBLE_SOLUTION_NONZEROS:
      break;

    case FEASIBLE_SOLUTION_USER:


#ifdef USE_SYM_APPLICATION
      CALL_USER_FUNCTION( user_receive_feasible_solution(env->user, msgtag,
							 env->best_sol.objval,
							 env->best_sol.xlength,
							 env->best_sol.xind,
							 env->best_sol.xval) );
#endif
      break;
   }

   return(FUNCTION_TERMINATED_NORMALLY);
}
