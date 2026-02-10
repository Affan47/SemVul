DrealEraseRecWin( Rectangle )

  rdsrec_list *Rectangle;
{
  drealrecwin *ScanRecWin;
  drealrecwin *DelRecWin;

  rdsbegin();

  if ( ! IsDrealOneWindow( Rectangle ) )
  {
    ScanRecWin = DREAL_WINDOW( Rectangle );

    do
    {
      DelRecWin  = ScanRecWin;
      ScanRecWin = ScanRecWin->NEXT;

      DrealFreeRecWin( DelRecWin );
    }
    while ( ScanRecWin != (drealrecwin *)NULL );
  }

  DREAL_WINDOW( Rectangle ) = (drealrecwin *)NULL;

  rdsend();
}
