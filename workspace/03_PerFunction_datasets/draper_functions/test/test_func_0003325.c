main(int argc, char *argv[])
{
   tStack   top;

   if (argc > 1 && argv[1][0] == '-' ) {
     if( argv[1][1] == 'l' ) {
       toLeda = true;

     }
   }


   n = ReadPoints();

   FindLowest();

   qsort(
      &P[1],
      n-1,
      sizeof( tsPoint ),
      Compare
   );


   if (ndelete_bit > 0) {
      Squash();

   }

   top = Graham();


   if (toLeda)
	PrintToLeda( top );
   else
   	PrintPostscript( top );
   return 0;
}
