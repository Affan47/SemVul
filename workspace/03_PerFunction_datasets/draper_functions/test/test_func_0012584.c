addzncvia(headvia,winznc,winrec, ptsig )
chain_list	*headvia;
WinZnc		*winznc;
GrgWindow	*winrec;
losig_list      *ptsig;
{
  chain_list	*intervia;
  chain_list	*scaninter;
  long		 mx=0,my=0,Mx=0,My=0,layer=0;
  rdsrec_list	*rec;
  rdsrec_list	*scanrec;
  chain_list	*scanvia;
  ptype_list    *ptl;

#ifdef BUILDRCNDEBUG
fprintf(stderr,"Traitement des vias\n");
#endif

  for(scanvia=headvia;scanvia;scanvia=scanvia->NEXT)
  {
    intervia=NULL;
    rec = (rdsrec_list*)(scanvia->DATA);
    do
    {
      ptl = getptype( rec->USER, RCN_SIG_PTR );
      if( !ptl )
      {
        rec = LYNX_LINK( rec );
        continue;
      }

      if( ptl->DATA == ptsig )
      {
        layer = GetRdsLayer( rec );
        if( !isviacontact( layer ) &&
            ( IsRcn( rec ) || RectangleDiff( rec ) )
          )
        {

          mx       = rec->X;
          my       = rec->Y;
          Mx       = rec->X+rec->DX;
          My       = rec->Y+rec->DY;
          intervia = GrgGetInterWindows(rec,winrec);

          if(intervia)
          {
            for(scaninter=intervia;scaninter;scaninter=scaninter->NEXT)
            {
              scanrec=(rdsrec_list*)(scaninter->DATA);


              {
                if(GETDIRECTION(scanrec)==HORIZ_DIR)
                {
                  my=min(my,scanrec->Y);
                  My=max(My,scanrec->Y+scanrec->DY);
                }
                else
                {
                  mx=min(mx,scanrec->X);
                  Mx=max(Mx,scanrec->X+scanrec->DX);
                }
              }
            }
            addznc(mx,my,Mx,My,layer,winznc);
            freechain(intervia);
          }
          else
            addznc(mx,my,Mx,My,layer,winznc);
        }
      }
      rec = LYNX_LINK( rec );
    }
    while( rec != scanvia->DATA );
  }
}
