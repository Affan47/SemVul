sym_get_row_lower(sym_environment *env, double *rowlb)
{
   if (!env->mip || !env->mip->m || !env->mip->rhs){
      if(env->par.verbosity >= 1){
	 printf("sym_get_row_lower():There is no loaded mip description or\n");
	 printf("there is no loaded row description!\n");
      }
      return(FUNCTION_TERMINATED_ABNORMALLY);
   }

   double upper;
   int i;
   double rhs, range, inf = SYM_INFINITY;
   char sense;

   for ( i = env->mip->m - 1; i >= 0; --i ){

	 rhs   = env->mip->rhs[i];
	 range = env->mip->rngval[i];
	 sense = env->mip->sense[i];

	 switch (sense) {
	  case 'E':
	     rowlb[i] = upper = rhs;
	     break;
	  case 'L':
	     rowlb[i] = -inf;
	     upper = rhs;
	     break;
	  case 'G':
	     rowlb[i] = rhs;
	     upper = inf;
	     break;
	  case 'R':
	     rowlb[i] = rhs - range;
	     upper = rhs;
	     break;
	  case 'N':
	     rowlb[i] = -inf;
	     upper = inf;
	     break;
	 }
      }

   return(FUNCTION_TERMINATED_NORMALLY);
}
