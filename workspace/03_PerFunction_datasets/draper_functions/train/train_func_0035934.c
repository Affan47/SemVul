phseg2TGrid(aptGrid, apPhSeg)
  eGrid_t    **aptGrid;
  phseg_list  *apPhSeg;
{
  long  y, yMin, yMax;


  if (apPhSeg->X1 == apPhSeg->X2) {
    if (!(LV_flags & F_ALLOW_OFFGRID)) {
      if ((apPhSeg->X1 - LV_phfig->XAB1) % XGRID) {
        wprinth((char*)NULL);
        wprintf("Segment \"%s\" (%d,%d) (%d,%d) is NOT on grid (skipped).\n",
                apPhSeg->NAME, apPhSeg->X1, apPhSeg->Y1,
                               apPhSeg->X2, apPhSeg->Y2);
        return;
      }
    }

    yMax = apPhSeg->Y2 - (apPhSeg->Y2 % YGRID);
    yMin = apPhSeg->Y1;
    if (apPhSeg->Y1 % YGRID) yMin += YGRID - (apPhSeg->Y1 % YGRID);

    if (LV_flags & F_NO_SPLIT_TERM) {
      addTGrid(aptGrid, apPhSeg->X1, yMin, apPhSeg->X1, yMax);
    } else {
      for(y = yMin; y <= yMax; y += YGRID)
        addTGrid(aptGrid, apPhSeg->X1, y, apPhSeg->X1, y);
    }
  } else {
    if (!(LV_flags & F_ALLOW_OFFGRID)) {
      if ((apPhSeg->Y1 - LV_phfig->YAB1) % YGRID) {
        wprinth((char*)NULL);
        wprintf("Segment \"%s\" (%d,%d) (%d,%d) is NOT on grid (skipped).\n",
                apPhSeg->NAME, apPhSeg->X1, apPhSeg->Y1,
                               apPhSeg->X2, apPhSeg->Y2);
        return;
      }
    }

    yMax = apPhSeg->X2 - (apPhSeg->X2 % XGRID);
    yMin = apPhSeg->X1;
    if (apPhSeg->X1 % XGRID) yMin += XGRID - (apPhSeg->X1 % XGRID);

    if (LV_flags & F_NO_SPLIT_TERM) {
      addTGrid(aptGrid, yMin, apPhSeg->Y1, yMax, apPhSeg->Y1);
    } else {
      for(y = yMin; y <= yMax; y += XGRID) {
        addTGrid(aptGrid, y, apPhSeg->Y1, y, apPhSeg->Y1);
      }
    }
  }
}
