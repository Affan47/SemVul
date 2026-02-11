retry_fwrite(char *b, size_t l, FILE *f, Hashes *hash)
   {
      size_t r = 1;
      while (r > 0 && l > 0)
      {
         r = fwrite(b, 1, l, f);
	 if (hash)
	    hash->Add((unsigned char*)b, r);
	 l -= r;
	 b += r;
      }
      return l == 0;
   }
