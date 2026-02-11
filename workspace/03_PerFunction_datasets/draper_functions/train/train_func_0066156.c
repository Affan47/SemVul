_inslbal(struct avln ** app)
{
  struct avln *ap = *app;

  switch (ap->bal) {
  case -1:

    {
      struct avln *ap1 = ap->l;

      if (ap1->bal == -1) {

	ap->l = ap1->r;
	ap1->r = ap;
	ap->bal = 0;
	ap = ap1;
      } else {

	struct avln *ap2 = ap1->r;

	ap1->r = ap2->l;
	ap2->l = ap1;
	ap->l = ap2->r;
	ap2->r = ap;
	ap->bal = (ap2->bal == -1) ? 1 : 0;
	ap1->bal = (ap2->bal == 1) ? -1 : 0;
	ap = ap2;
      }
      ap->bal = 0;
      *app = ap;
    }
    return 0;
  case 0:
    ap->bal = -1;
    return 1;
  case 1:
    ap->bal = 0;
    return 0;
  default:
    Abort("%t avlinsert(): abort: bad balance factor = %d\n",
	  ap->bal);
  }

}
