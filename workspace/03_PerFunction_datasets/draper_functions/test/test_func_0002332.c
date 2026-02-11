asm_GetInputSection (pt_fig, ident)

struct asfig *pt_fig;
char         *ident ;

  {
  struct asisc  *pt_isc  = NULL;

  if (pt_fig != NULL)
    {
    pt_isc = pt_fig->IN_SEC;
    while (pt_isc != NULL)
      {
      if (pt_isc->IDENT == ident)
        break;
      pt_isc = pt_isc->NEXT;
      }
    }

  return (pt_isc);
  }
