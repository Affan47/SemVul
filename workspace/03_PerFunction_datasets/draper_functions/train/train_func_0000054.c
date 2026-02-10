set_db_type(const char *name)
{
   if (catalog_db != NULL) {
      free(catalog_db);
   }
   catalog_db = bstrdup(name);
}
