close()
   {
      if (!file) return NULL;
      int res = gzclose(file);
      file = NULL;
      return res == Z_OK ? this : NULL;
   }
