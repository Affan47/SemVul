utl_ccputtyp (pt_src, pt_cnd)

struct uttyp  *pt_src;
int          (*pt_cnd) ();

  {
  struct uttyp *pt_typ = NULL;


  if (pt_cnd == NULL)
    {
    while (pt_src != NULL)
      {
      pt_typ = utl_adduttyp (pt_typ, pt_src->DAT1, pt_src->DAT2);
      pt_src = pt_src->NEXT;
      }
    }
  else
    {
    while (pt_src != NULL)
      {
      if ((*pt_cnd) (pt_src) != 0)
        pt_typ = utl_adduttyp (pt_typ, pt_src->DAT1, pt_src->DAT2);

      pt_src = pt_src->NEXT;
      }
    }

  pt_typ = utl_revuttyp (pt_typ);

  return (pt_typ);
  }
