getNumberFromBuffer(const char* buffer, const char* s) {
    const char* p = buffer;
    int slen = strlen(s);
    while(1) {
      if(*p == '\0')
	return -11;

      if(memcmp(p, s, slen) == 0)
	{
	  int number;


	  while(*p != ' ' && *p != '\t' && *p != '\n' && *p != '\0')
	    p++;

	  while(*p == ' ' || *p == '\t')
	    p++;

	  number = atoi(p);

	  while(*p != ' ' && *p != '\t' && *p != '\n' && *p != '\0')
	    p++;

	  while(*p == ' ' || *p == '\t')
	    p++;

	  if(memcmp(p, "kB", 2) != 0)
	    return -22;
	  return number;
	}

      while(*p != '\n' && *p != '\0')
	p++;
      p++;
    }
    return -33;
  }
