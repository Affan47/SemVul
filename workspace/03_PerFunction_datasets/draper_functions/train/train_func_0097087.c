debugctc ( losig_list *headlosig, int niveau )
{
  losig_list            *scanlosig;
  chain_list            *scanctc;
  chain_list            *scanctc2;
  loctc_list            *ptctc;


  for( scanlosig = headlosig ; scanlosig ; scanlosig = scanlosig->NEXT )
  {
    if( ! scanlosig->PRCN )
      continue;

    for( scanctc = scanlosig->PRCN->PCTC ; scanctc ; scanctc = scanctc->NEXT )
    {
      ptctc = (loctc_list*)( scanctc->DATA );
      if( getptype( ptctc->USER, FLATTEN_CTC ) )
      {
        printf( "(%d) FLATTEN_CTC trouve dans la CTC (%lX)  entre %ld.%ld et %ld.%ld.\n",
                niveau,
                (unsigned long)ptctc,
                ptctc->SIG1->INDEX,
                ptctc->NODE1,
                ptctc->SIG2->INDEX,
                ptctc->NODE2
              );
        exit(-1);
      }

      for( scanctc2 = ( ptctc->SIG1 == scanlosig ? ptctc->SIG2 : ptctc->SIG1 )->PRCN->PCTC ;
           scanctc2 ;
           scanctc2 = scanctc2->NEXT )
      {
        if( scanctc2->DATA == ptctc )
          break;
      }
      if( !scanctc2 )
      {
        printf( "(%d) CTC (%lX) entre %ld:%ld et %ld:%ld sur signal %ld non trouvee sur l'autre signal.\n",
                niveau,
                (unsigned long)ptctc,
                ptctc->SIG1->INDEX, ptctc->NODE1,
                ptctc->SIG2->INDEX, ptctc->NODE2,
                scanlosig->INDEX
              );
        exit(-1);
      }
    }
  }
}
