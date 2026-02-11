vbh_frevbfig (listvbfig)

struct vbfig *listvbfig;

{
  struct vbfig *ptvbfig;


  while (listvbfig != NULL)
  {
    vbh_frevbatr (listvbfig->BEATR);
    vbh_frevbaux (listvbfig->BEAUX);
    vbh_frevbcst (listvbfig->BECST);
    vbh_frevbgen (listvbfig->BEGEN);
    vbh_frevbpor (listvbfig->BEPOR);
    vbh_frevbpcs (listvbfig->BEPCS);
    vbh_frevbfun (listvbfig->BEFUN);
    vbh_frevbtyp (listvbfig->BETYP);
    vbh_frevbmod (listvbfig->BEMOD);
    vbh_frevbins (listvbfig->BEINS);
    vbh_frevbgnr (listvbfig->BEGNR);

    destroyauthtable( listvbfig->HASH_TYPE );

    freechain( listvbfig->PACK_LIST );

    ptvbfig   = listvbfig;
    listvbfig = listvbfig->NEXT;
    autfreeblock (ptvbfig);
  }

}
