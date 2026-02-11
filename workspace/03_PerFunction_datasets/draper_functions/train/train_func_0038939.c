DrealAddRectangle( Name, Layer, X, Y, Dx, Dy )

   char        *Name;
   char         Layer;
   long         X;
   long         Y;
   long         Dx;
   long         Dy;
{
  rdsrec_list *ScanRec;

  rdsbegin();

  ScanRec = addrdsfigrec( DrealFigureRds, Name, Layer, X, Y, Dx, Dy );

  DrealInsertRectangle( ScanRec );

  if ( ScanRec->NEXT != (rdsrec_list *)0 )
  {
    DREAL_PREVIOUS_L( ScanRec->NEXT ) = &ScanRec->NEXT;
  }

  DREAL_PREVIOUS_L( ScanRec ) = &DrealFigureRds->LAYERTAB[ Layer ];

  rdsend();
  return( ScanRec );
}
