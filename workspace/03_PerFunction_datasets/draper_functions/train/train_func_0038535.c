getColor() const
{
   if ( color == DI_Color(0)) {
      switch ( player ) {
         case 0: return DI_Color( 0xe0, 0, 0 );
         case 1: return DI_Color( 0, 0x71, 0xdb );
         case 2: return DI_Color( 0xbc, 0xb3, 0 );
         case 3: return DI_Color( 0, 0xaa, 0 );
         case 4: return DI_Color( 0xbc, 0, 0 );
         case 5: return DI_Color( 0xb2, 0, 0xb2 );
         case 6: return DI_Color( 0,0, 0xaa );
         case 7: return DI_Color( 0xbc, 0x67, 0 );
         case 8: return DI_Color( 0xaa, 0xaa, 0xaa );
      };
      return DI_Color(0, 0, 0);
   } else
      return color;
}
