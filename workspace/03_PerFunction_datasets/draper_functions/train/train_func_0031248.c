GrgChkInConFEqui(fig)
lofig_list      *fig;


{
  losig_list    *ScanLoSig;
  rdsrec_list   *ScanPhRec;
  char           EndEqui;
  loins_list    *ScanLoIns;
  lotrs_list    *ScanLoTrs;
  locon_list    *ScanLoCon;

  for(ScanLoSig=fig->LOSIG; ScanLoSig; ScanLoSig=ScanLoSig->NEXT)
  {
    EndEqui=0;
    ScanPhRec=(rdsrec_list*)(getptype(ScanLoSig->USER,RCN_FEQUI)->DATA);
    while(!EndEqui)
    {
      if(ScanPhRec==NULL)
	GrgFatalError(22);
      ScanPhRec->USER=NULL;
      if(IsLynxEndEqui(ScanPhRec))
	EndEqui=1;
      else
	ScanPhRec=LYNX_EQUI(ScanPhRec);
    }
  }
  for(ScanLoCon=fig->LOCON; ScanLoCon; ScanLoCon=ScanLoCon->NEXT)
  {
    if(!getptype(ScanLoCon->USER,RDSLOCON1))
      GrgFatalError(23);
  }
  for(ScanLoIns=fig->LOINS; ScanLoIns; ScanLoIns=ScanLoIns->NEXT)
  {
    for(ScanLoCon=ScanLoIns->LOCON; ScanLoCon; ScanLoCon=ScanLoCon->NEXT)
    {
      if(!getptype(ScanLoCon->USER,RDSLOCON2))
	GrgFatalError(24);
    }
  }
  for(ScanLoTrs=fig->LOTRS; ScanLoTrs; ScanLoTrs=ScanLoTrs->NEXT)
  {
    if(!getptype(ScanLoTrs->DRAIN->USER,RDSLOCON3))
      GrgFatalError(25);
    if(!getptype(ScanLoTrs->GRID->USER,RDSLOCON3))
      GrgFatalError(25);
    if(!getptype(ScanLoTrs->SOURCE->USER,RDSLOCON3))
      GrgFatalError(25);
  }
}
