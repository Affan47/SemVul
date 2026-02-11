analyze_exefile( void )
{
   int c, i;

   if ( story_offset > 0 )
   {

      return FALSE;
   }


   jz_rewind( gfp );
   i = 0;

   while ( ( c = jz_getc( gfp ) ) > -1 )
   {
      if ( c != magic[i] )
      {
         if ( c == magic[0] )
         {
            i = 1;
         }
         else
         {
            i = 0;
         }
      }
      else if ( ++i == MAGIC_END )
      {

         if ( jz_getc( gfp ) != 0 )
         {
            return FALSE;
         }


         story_offset = jz_getc( gfp );
         story_offset += 256L * jz_getc( gfp );
         story_offset += 65536L * jz_getc( gfp );
         return TRUE;
      }
   }

   return FALSE;

}
