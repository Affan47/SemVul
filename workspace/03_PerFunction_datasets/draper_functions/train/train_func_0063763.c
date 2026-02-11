FvhFbhScanProcess( FbhFigure, FsmFigure )

  fbfig_list  *FbhFigure;
  fsmfig_list *FsmFigure;
{
  fbpcs_list *ScanProcess;
  fbpcsinfo  *ProcInfo;
  int         Number;

  Number = 0;

  for ( ScanProcess  = FbhFigure->BEPCS;
        ScanProcess != (fbpcs_list *)0;
        ScanProcess  = ScanProcess->NEXT )
  {
    ProcInfo = (fbpcsinfo *)autallocheap( sizeof( fbpcsinfo ) );
    ProcInfo->HASH_READ  = createauthtable( 50 );
    ProcInfo->HASH_WRITE = createauthtable( 50 );
    ScanProcess->USER = (void *)ProcInfo;

    FvhProcInfo = ProcInfo;

    FbhScanExprProcess( ScanProcess, FvhFbhScanLeftExpr, FvhFbhScanRightExpr );

# ifdef DEBUG
    {
      chain_list *ScanList;

      fprintf( stdout, "Process %s:\n", ScanProcess->LABEL );

      fprintf( stdout, "READ\n" );
      for ( ScanList  = ProcInfo->READ_LIST;
            ScanList != (chain_list *)0;
            ScanList  = ScanList->NEXT )
      {
        fprintf( stdout, "%s\n", (char *)ScanList->DATA );
      }

      fprintf( stdout, "WRITE\n" );
      for ( ScanList  = ProcInfo->WRITE_LIST;
            ScanList != (chain_list *)0;
            ScanList  = ScanList->NEXT )
      {
        fprintf( stdout, "%s\n", (char *)ScanList->DATA );
      }
    }
# endif

    Number++;
  }

  if ( Number & 1 )
  {
    fvherror( FVH_ERROR_TWO_PROCESS, FsmFigure->NAME, 0 );
  }

  return( Number );
}
