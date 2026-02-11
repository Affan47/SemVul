SxLib2ALUxOBS(aLayer)
  char  aLayer;
{
  phseg_list *pPhSeg;
        long  fComp, fFirst, X1, Y1, X2, Y2, Ext;


  Ext = getLayerExt(aLayer);

  fFirst = TRUE;


  for(pPhSeg = LV_phfig->PHSEG; pPhSeg != NULL; pPhSeg = pPhSeg->NEXT) {
    fComp = cmpALU(aLayer, pPhSeg->LAYER);

    if (!(fComp & F_EQUAL)) continue;
    if (  fComp & F_CALU  ) continue;

    switch(pPhSeg->TYPE) {
      case LEFT:
      case RIGHT:
      default:
        X1 = pPhSeg->X1 - Ext;
        X2 = pPhSeg->X2 + Ext;
        Y1 = pPhSeg->Y1 - pPhSeg->WIDTH / 2;
        Y2 = pPhSeg->Y2 + pPhSeg->WIDTH / 2;
        break;
      case UP:
      case DOWN:
        X1 = pPhSeg->X1 - pPhSeg->WIDTH / 2;
        X2 = pPhSeg->X2 + pPhSeg->WIDTH / 2;
        Y1 = pPhSeg->Y1 - Ext;
        Y2 = pPhSeg->Y2 + Ext;
        break;
    }

    if (fFirst) {
      fFirst = FALSE;
      m_AddObs(LV_pMACRO->lOBS, C_OBSITEM_LAYER, (long)aLayer);
    }

    m_AddObs(LV_pMACRO->lOBS, C_OBSITEM_RECT, m_AddRect(X1, Y1, X2, Y2));
  }
}
