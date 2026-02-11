Lynxviambkrds( FigureRds, Via )

  rdsfig_list *FigureRds;
  phvia_list  *Via;
{
  rdsrec_list *Rectangle;
  rdsrec_list *ScanRec;

  rdsbegin();

  ScanRec = Rectangle = viambkrds( FigureRds, Via, 1 );

  if ( Rectangle == (rdsrec_list *)0 )
  {
    rdsend();
    return;
  }

  SetLynxFirstLink( Rectangle );

  do
  {
    SetLynxAttribute( ScanRec, Via->TYPE );

    LYNX_LINK( ScanRec ) = (rdsrec_list *)ScanRec->USER;
    ScanRec              = (rdsrec_list *)ScanRec->USER;
  }
  while ( ScanRec != Rectangle );

  rdsend();
}
