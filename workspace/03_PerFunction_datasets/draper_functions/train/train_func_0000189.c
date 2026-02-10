dupablchain(chain_list* ablchain)
{
   chain_list* chain,*res=NULL;

   for (chain=ablchain;chain;chain=chain->NEXT) {
      res=addchain(res,dupablexpr(chain->DATA));
   }

   return res;
}
