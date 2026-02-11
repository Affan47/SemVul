read ( tnstream& stream )
{
   int version = stream.readInt();
   if ( version > vehicleHeightChangeMethodVersion || version < 1 ) {
      ASCString s = "invalid version for reading VehicleType :: HeightChangeMethod : ";
      s += strrr ( version );
      throw ASCmsgException ( s );
   }
   startHeight = stream.readInt();
   heightDelta = stream.readInt();
   moveCost = stream.readInt();
   canAttack = stream.readInt();
   dist = stream.readInt();
}
