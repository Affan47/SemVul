lcl_addpacom (lastpacom, text, position)

struct pacom   *lastpacom;
char           *text;
unsigned short  position;

  {
  struct pacom *ptcom = NULL;

  if (FRE_COMPNT == NULL)
     ptcom = pat_addpacom (lastpacom, text, position);
  else
    {
    ptcom           = FRE_COMPNT;
    FRE_COMPNT      = ptcom->NEXT;

    ptcom->TEXT     = text;
    ptcom->POSITION = position;
    ptcom->NEXT     = lastpacom;
    }

  return (ptcom);
  }
