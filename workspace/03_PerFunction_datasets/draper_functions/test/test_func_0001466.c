beh_rmvbepor (listbepor, beporname)

struct bepor *listbepor;
char         *beporname;

  {
  struct bepor  headpor;
  struct bepor *ptlastpor;
  struct bepor *ptbepor;

  if (listbepor != NULL)
    {


    headpor.NEXT = listbepor;
    headpor.NAME = NULL     ;
    ptbepor      = &headpor;
    while ((ptbepor != NULL) && (ptbepor->NAME != beporname))
      {
      ptlastpor = ptbepor;
      ptbepor   = ptbepor->NEXT;
      }

    if (ptbepor != NULL)
      {


      ptlastpor->NEXT = ptbepor->NEXT;
      autfreeblock (ptbepor);
      }

    listbepor = headpor.NEXT;
    }

  return(listbepor);
  }
