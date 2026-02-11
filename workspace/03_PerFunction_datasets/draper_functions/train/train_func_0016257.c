GraalAddDruc( DrucRec )

   rdsrec_list *DrucRec;
{
  rdsrec_list *ScanDrucRec;
  rdsrec_list *ScanRec;
  rdsrec_list *First;
  rdsrec_list *Link;

  rdsbegin();

  First = (rdsrec_list *)NULL;

  if ( ! IsGraalDruc( DrucRec ) )
  {
    ScanDrucRec = DrucRec;

    do
    {
      ScanRec =

        addrdsfigrec( GraalFigureRds, ScanDrucRec->NAME,
                      GetRdsLayer( ScanDrucRec ),
                      ScanDrucRec->X, ScanDrucRec->Y,
                      ScanDrucRec->DX, ScanDrucRec->DY );

      SetGraalDruc( ScanRec );
      SetGraalDruc( ScanDrucRec );

      if ( ScanRec->NEXT != (rdsrec_list *)NULL )
      {
        GRAAL_PREVIOUS( ScanRec->NEXT ) = &ScanRec->NEXT;
      }

      GRAAL_PREVIOUS( ScanRec ) =

        &GraalFigureRds->LAYERTAB[ GetRdsLayer( ScanRec ) ];

      GraalInsertRectangle( ScanRec );

      if ( First == (rdsrec_list *)NULL )
      {
        First = ScanRec;
        Link  = ScanRec;
      }
      else
      {
        Link->USER = (void *)ScanRec;
        Link       = ScanRec;
      }

      ScanDrucRec = MACRO_NEXT_EQUI( ScanDrucRec );
    }
    while ( ScanDrucRec != DrucRec );

    Link->USER = (void *)First;
  }

  rdsend();
  return( First );
}
