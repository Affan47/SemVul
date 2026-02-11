drmaa_fill_string_vector(const char *name[])
{
   drmaa_attr_names_t *vector;
   int  i;

   DENTER(TOP_LAYER, "drmaa_fill_string_vector");


   if (!(vector=(drmaa_attr_names_t *)japi_allocate_string_vector(JAPI_ITERATOR_STRINGS))) {
      DRETURN(NULL);
   }

   for (i=0; name[i]; i++) {
      DPRINTF(("adding \"%s\"\n", name[i]));
      if (!lAddElemStr(&(vector->it.si.strings), ST_name, name[i], ST_Type)) {
         japi_delete_string_vector((drmaa_attr_values_t *)vector);
         DRETURN(NULL);
      }
   }


   vector->it.si.next_pos = lFirst(vector->it.si.strings);

   DRETURN(vector);
}
