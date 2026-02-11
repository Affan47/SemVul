locate_word(char* wordPtr)
{
   for( ; *data_ptr != CHAR_EOF ; data_ptr++ )
   {
      if( *data_ptr == *wordPtr )
      {
         for( ; *data_ptr == *wordPtr && *wordPtr ; data_ptr++, wordPtr++ );

         if( *wordPtr == '\0' )
         {
            next_token();
            return data_ptr;
         }
      }
   }

   return NULL;
}
