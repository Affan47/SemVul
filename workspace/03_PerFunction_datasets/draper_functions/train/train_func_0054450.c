sym_set_row_upper(sym_environment *env, int index, double value)
{
   double rhs, range, lower = 0, upper = 0, inf = SYM_INFINITY;
   char   sense;
   int i;

   if (!env->mip || !env->mip->m || index > env->mip->m || index < 0 ||
       !env->mip->rhs){
      if(env->par.verbosity >= 1){
	 printf("sym_set_row_upper():There is no loaded mip description or\n");
	 printf("index is out of range or no row description!\n");
      }
      return(FUNCTION_TERMINATED_ABNORMALLY);
   }

   rhs   = env->mip->rhs[index];
   range = env->mip->rngval[index];
   sense = env->mip->sense[index];

   switch (sense) {
    case 'E':
       lower = upper = rhs;
       break;
    case 'L':
       lower = -inf;
       upper = rhs;
       break;
    case 'G':
       lower = rhs;
       upper = inf;
       break;
    case 'R':
       lower = rhs - range;
       upper = rhs;
       break;
    case 'N':
       lower = -inf;
       upper = inf;
       break;
   }


   if ( upper != value ) {
      upper = value;

      range = 0.0;
      if (lower > -inf) {
	 if (upper < inf) {
	    rhs = upper;
	    if (upper==lower) {
	       sense = 'E';
	    }else{
	       sense = 'R';
	       range = upper - lower;
	    }
	 }else{
	    sense = 'G';
	    rhs = lower;
	 }
      }else{
	 if (upper < inf) {
	    sense = 'L';
	    rhs = upper;
	 }else{
	    sense = 'N';
	    rhs = 0.0;
	 }
      }

      env->mip->sense[index] = sense;
      env->mip->rhs[index] = rhs;
      env->mip->rngval[index] = range;
   }

   if (env->mip->change_num){
      for(i = env->mip->change_num - 1 ; i >=0 ; i--){
	 if (env->mip->change_type[i] == RHS_CHANGED){
	    break;
	 }
      }
      if (i < 0 ){
	 env->mip->change_type[env->mip->change_num] = RHS_CHANGED;
	 env->mip->change_num++;

      }
   }
   else{
      env->mip->change_type[env->mip->change_num] = RHS_CHANGED;
      env->mip->change_num++;

   }

   return(FUNCTION_TERMINATED_NORMALLY);
}
