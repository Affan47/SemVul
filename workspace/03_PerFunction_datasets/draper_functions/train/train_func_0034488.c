debugctc2 ( lofig_list *ptfig )
{
   losig_list   *sig;
   chain_list   *scanchain;
   loctc_list   *ptctc;

   printf( "Information sur la figure %s.\n", ptfig->NAME );
   for( sig = ptfig->LOSIG ; sig ; sig = sig->NEXT )
   {
     printf( "Signal %2ld (%08X)\n", sig->INDEX, (unsigned long) sig );
     if( sig->PRCN )
     {
       for( scanchain = sig->PRCN->PCTC ;
            scanchain ;
            scanchain = scanchain->NEXT
          )
       {
         ptctc = ( loctc_list* )( scanchain->DATA );
         printf(
                "  CTC (%lX) entre le signal %2ld (%lX) et le signal %2ld (%lX).\n",
                 (unsigned long)ptctc,
                 ptctc->SIG1->INDEX,
                 (unsigned long)ptctc->SIG1,
                 ptctc->SIG2->INDEX,
                 (unsigned long)ptctc->SIG2
               );
       }
     }
   }
}
