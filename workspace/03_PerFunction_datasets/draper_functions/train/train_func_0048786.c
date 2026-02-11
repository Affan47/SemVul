gribfill (gaint eoff, gaint ioff, gaint joff, gaint nsiz, struct grhdr *ghdr, struct gaindx *pindx) {
gaint boff,koff;

  koff = nsiz*(eoff+ioff) + joff;
  if (bigflg) {
    boff = 2*(eoff+ioff) + joff;
    *(pindxb->bigpnt+boff) = ghdr->ldpos;
    if (ghdr->bmsflg) *(pindxb->bigpnt+boff+1) = ghdr->lbpos;
    boff = (eoff+ioff) + joff;
    *(pindx->intpnt+boff) = ghdr->bnum;
  } else {
    *(pindx->intpnt+koff) = ghdr->dpos;
    if (ghdr->bmsflg) *(pindx->intpnt+koff+1) = ghdr->bpos;
    *(pindx->intpnt+koff+2) = ghdr->bnum;
  }
  *(pindx->fltpnt+koff)   = ghdr->dsf;
  *(pindx->fltpnt+koff+1) = ghdr->bsf;
  *(pindx->fltpnt+koff+2) = ghdr->ref;
}
