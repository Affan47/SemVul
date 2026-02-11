put_arity_abl (chain_list* abl)
{
   chain_list* pattern;
   int arity;


   if (ABL_ATOM (abl)) return;

   arity=0;
 	for (pattern = ABL_CDR (abl); pattern; pattern=ABL_CDR(pattern)) {
     arity++;
     put_arity_abl((chain_list*)ABL_CAR(pattern));
	}

   ABL_ARITY_L(abl)=arity;
   return ;
}
