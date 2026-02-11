LynxDumpAllEqui( FigureRds, HeadEqui, Figure, Real )

  rdsfig_list *FigureRds;
  rdsrec_list *HeadEqui;
  void        *Figure;
  char         Real;
{
  rdsrec_list *ScanEqui;

  rdsbegin();

  Lynxrecrdsmbk( Figure, FigureRds->LAYERTAB[ RDS_ABOX ], Real );

  for ( ScanEqui  = HeadEqui;
        ScanEqui != (rdsrec_list *)0;
        ScanEqui  = LYNX_EQUI( ScanEqui ) )
  {
    Lynxrecrdsmbk( Figure, ScanEqui, Real );
  }

  rdsend();
}
