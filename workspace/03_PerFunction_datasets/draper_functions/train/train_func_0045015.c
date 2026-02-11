checkcursorpos ( void )
{
   if ( cursor >= 0 ) {
      checkcursor();
      if ( ps.line1num + cursory >= maxlinenum ) {
         ps.line1num = maxlinenum - cursory - 1;
         display();
         checkscrollup();
         checkscrolldown();
         return 0;
      }

      if( ps.line1num + cursory < 0 ) {
         ps.line1num = -cursory;
         display();
         checkscrollup();
         checkscrolldown();
         return 0;
      }
   }
   return 1;
}
