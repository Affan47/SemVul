alpha_search (
   const char *findme,
   const String *base,
   int qty,
   Boolean are_sorted )
{
   int i;

   if ( are_sorted )
      return ( (String*) bsearch( &findme, (const void*) base, qty, sizeof(String), alpha_cmp ) );

   for ( i=0; i<qty; i++ )
      if ( !strcmp ( findme, base[i] ) )
         break;
   if ( i==qty )
      return (String*)0;

   return ((String*)(base + i));
}
