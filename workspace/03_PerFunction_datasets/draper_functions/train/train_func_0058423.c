Squash( void )
{
   int i, j;
   i = 0; j = 0;

   while ( i < n ) {

      if ( !P[i].delete_bit ) {
         Copy( i, j );
         j++;
      }

      i++;
   }
   n = j;


}
