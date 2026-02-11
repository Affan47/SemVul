datum_dup (datum_t *src)
{
   datum_t *dest;

   dest = malloc(sizeof(datum_t));
   if( dest == NULL )
      return NULL;

   dest->data = malloc(src->size);
   if ( dest->data == NULL )
      {
         free(dest);
         return NULL;
      }

   dest->size = src->size;
   memcpy(dest->data, src->data, src->size);
   return dest;
}
