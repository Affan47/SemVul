vbh_frevbarg (listvbarg)

struct vbarg *listvbarg;

{
  struct vbarg *ptvbarg;


  while (listvbarg != NULL)
  {
    freevexexpr (listvbarg->TARGET);

    ptvbarg   = listvbarg;
    listvbarg = listvbarg->NEXT;
    autfreeheap (ptvbarg, sizeof(struct vbarg));
  }
}
