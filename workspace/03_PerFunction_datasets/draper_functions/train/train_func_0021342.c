ilt_cache_load(char *table_name)
{
   insn_lookup_t *ilt;
   char *filename;
   FILE *fd;

   if (!(filename = ilt_build_filename(table_name)))
      return NULL;

   if (!(fd = fopen(filename,"rb"))) {
      free(filename);
      return NULL;
   }

   ilt = ilt_load_table(fd);
   fclose(fd);
   free(filename);
   return ilt;
}
