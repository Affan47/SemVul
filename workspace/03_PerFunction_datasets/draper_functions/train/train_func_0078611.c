datum_new ( void *data, size_t size )
{
   datum_t *datum;

   datum = malloc( sizeof(datum_t));
   if ( datum == NULL )
      return NULL;

   datum->data = malloc( size );
   if ( datum->data == NULL )
      {
         free(datum);
         return NULL;
      }

   datum->size = size;
   memcpy(datum->data, data, datum->size);
   return datum;
}
