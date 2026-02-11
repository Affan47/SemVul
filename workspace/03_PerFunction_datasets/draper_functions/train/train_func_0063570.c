getFieldThreat ( int x, int y )
{
   if ( !fieldInformation )
      calculateFieldInformation ();
   return fieldInformation[y * activemap->xsize + x ].threat;
}
