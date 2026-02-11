eina_array_accessor_get_at(Eina_Accessor_Array *it,
                           unsigned int idx,
                           void **data)
{
   EINA_MAGIC_CHECK_ARRAY_ACCESSOR(it, EINA_FALSE);

   if (!(idx < eina_array_count(it->array)))
      return EINA_FALSE;

   if (data)
      *data = eina_array_data_get(it->array, idx);

   return EINA_TRUE;
}
