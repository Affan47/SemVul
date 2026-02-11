getc(FILE *fp)
{
    extern FILE* yyin;

    static bool bangflag = false;
    static bool backflag = false;

    static bool eolflag = false;

    if ((size_t)(lineptr - linebuf) > sizeof linebuf)
      ick_lose(IE666, iyylineno, (char *)NULL);

    if (bangflag)
    {
	bangflag = false;

	return('.');
    }
    else if (backflag)
    {
	backflag = false;

	return('H');
    }
    else
    {
      int c;
      char c_char;
      size_t dummy;


      c_char=0;
      dummy = fread(&c_char,1,1,fp);


      if(c_char=='\r') dummy = fread(&c_char,1,1,fp);
      c = c_char;

      if(feof(fp)) c=EOF;
      if(!eolflag && c == EOF) c = '\n';


      if (feof(yyin))
      {
	*lineptr = '\0';
	if(eolflag) return(EOF);
	if(c=='\0' || c==EOF) c='\n';
      }

      eolflag = false;

      if (c == '!')
      {
	*lineptr++ = '!';
	bangflag = true;
	return(c = '\'');
      }
      else if (c == '\b')

      {
	*lineptr++ = '\b';
	backflag = true;
	return(c = '^');
      }
      else if (c == '\n')
      {
	*lineptr = '\0';
	lineptr = linebuf;
	if (iyylineno >= textlinecount)
	{
	  textlinecount += ALLOC_CHUNK;
	  if (textlines)
	    textlines = realloc(textlines,
				textlinecount * sizeof(char*));
	  else
	    textlines = malloc(textlinecount * sizeof(char*));
	  if (!textlines)
	    ick_lose(IE666, iyylineno, (char *)NULL);
	}
	textlines[iyylineno] = malloc(1 + strlen(linebuf));
	if (!textlines[iyylineno])
	  ick_lose(IE666, iyylineno, (char *)NULL);
	strcpy(textlines[iyylineno], linebuf);
	iyylineno++;
	eolflag=true;
	return('\n');
      }
      else
      {
	return(*lineptr++ = c);
      }
    }
}
