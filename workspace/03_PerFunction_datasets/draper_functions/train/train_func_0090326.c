GraalEraseWindow()

{
  long         Offset;
  graalwin    *ScanWin;
  graalwinrec *ScanWinRec;
  graalwinrec *DelWinRec;
  char         Layer;

  rdsbegin();

  for ( Offset = 0; Offset < GraalWindowSize; Offset++ )
  {
    ScanWin = &GraalWindowTable[ Offset ];

    if ( ScanWin->LAYERTAB != (graalwinrec **)NULL )
    {
      for ( Layer = 0; Layer < RDS_MAX_LAYER; Layer++ )
      {
        ScanWinRec  = ScanWin->LAYERTAB[ Layer ];

        while ( ScanWinRec != (graalwinrec *)NULL )
        {
          DelWinRec   = ScanWinRec;
          ScanWinRec  = ScanWinRec->NEXT;

          GraalFreeWinRec( DelWinRec );
        }
      }

      GraalFreeWinLayer( ScanWin );
    }
  }

  rdsend();
}
