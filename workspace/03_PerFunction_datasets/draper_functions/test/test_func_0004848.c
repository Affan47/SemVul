_mesa_alloc_dispatch_table()
{


   GLint numEntries = MAX2(_glapi_get_dispatch_table_size(), _gloffset_COUNT);
   struct _glapi_table *table;

   table = malloc(numEntries * sizeof(_glapi_proc));
   if (table) {
      _glapi_proc *entry = (_glapi_proc *) table;
      GLint i;
      for (i = 0; i < numEntries; i++) {
         entry[i] = (_glapi_proc) _mesa_generic_nop;
      }
   }
   return table;
}
