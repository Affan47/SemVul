skip_lines(FILE *i, int n)
   {
      char buffer[BLOCK_SIZE];
      while (n > 0) {
	 if (fgets(buffer, sizeof(buffer), i) == 0)
	    buffer[0] = '\0';
	 size_t const l = strlen(buffer);
	 if (l == 0 || buffer[l-1] == '\n')
	    n--;
      }
   }
