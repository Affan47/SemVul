beh_frebiabl (listbiabl)

struct biabl *listbiabl;

  {
  struct biabl *ptbiabl;


  while (listbiabl != NULL)
    {
    freeablexpr (listbiabl->VALABL);
    freeablexpr (listbiabl->CNDABL);
    freeptype(listbiabl->USER);

    ptbiabl   = listbiabl;
    listbiabl = listbiabl->NEXT;
    autfreeblock (ptbiabl);
    }

  }
