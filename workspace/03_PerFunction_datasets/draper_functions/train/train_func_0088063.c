vbh_frevbgnr (listvbgnr)

struct vbgnr *listvbgnr;

{
  struct vbgnr *ptvbgnr;


  while (listvbgnr != NULL)
    {
      freevexexpr( listvbgnr->FOR_VARIABLE );
      freevexexpr( listvbgnr->FOR_LEFT     );
      freevexexpr( listvbgnr->FOR_RIGHT    );
      freevexexpr( listvbgnr->IF_COND      );

      vbh_frevbpcs( listvbgnr->BEPCS );
      vbh_frevbins( listvbgnr->BEINS );
      vbh_frevbgnr( listvbgnr->BEGNR );

    ptvbgnr   = listvbgnr;
    listvbgnr = listvbgnr->NEXT;
    autfreeheap (ptvbgnr, sizeof(struct vbgnr));
    }

}
