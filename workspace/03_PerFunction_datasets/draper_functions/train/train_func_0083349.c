sym_get_row_range(sym_environment *env, double *rowrng)
{
   if (!env->mip || !env->mip->m){
      if(env->par.verbosity >= 1){
	 printf("sym_get_row_range():There is no loaded mip description or\n");
	 printf("there is no loaded row description!\n");
      }
      return(FUNCTION_TERMINATED_ABNORMALLY);
   }

   memcpy(rowrng, env->mip->rngval, DSIZE * env->mip->m);

   return(FUNCTION_TERMINATED_NORMALLY);

}
