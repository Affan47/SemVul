VasySimulateViewSimul( ScanSimul )

  vasysimul *ScanSimul;
{
  char    *Value;
  int      Position;
  int      Width;

  VasyPrintf( stdout, "    --> VasySimulateViewSimul %d %d\n",
             ScanSimul->WIDTH, ScanSimul->SIGNED );

  Value   = ScanSimul->VALUE;
  Width   = ScanSimul->WIDTH;

  for ( Position = 0; Position < Width; Position++ )
  {
    VasyPrintf( stdout, "    +++ Simul[ %d ] > %c\n",
               Position, VEX_LITERAL_BY_ID[ (int)Value[ Position ] ] );
  }

  VasyPrintf( stdout, "    <-- VasySimulateViewSimul\n" );
}
