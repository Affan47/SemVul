setclipping ( void )
{
   bar ( x1, y1, x1 + xsize, y1 + ysize, 255 );
   if ( next )
      next->setclipping ( );
}
