eina_array_free(Eina_Array *array)
{
   eina_array_flush(array);

   EINA_SAFETY_ON_NULL_RETURN(array);
   EINA_MAGIC_CHECK_ARRAY(array);
   MAGIC_FREE(array);
}
