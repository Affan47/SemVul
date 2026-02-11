phseg2PINS()
{
  phseg_list *pPhSeg;
  locon_list *pLoCon;
      ePIN_t *pPIN;
     eGrid_t *tCALU;


  for(pPhSeg  = LV_phfig->PHSEG;
      pPhSeg != (phseg_list*)NULL;
      pPhSeg  = pPhSeg->NEXT) {
    if (isvdd(pPhSeg->NAME)) continue;
    if (isvss(pPhSeg->NAME)) continue;

    switch(pPhSeg->LAYER) {
      case CALU1:
      case CALU2:
      case CALU3:
      case CALU4:
      case CALU5:
      case CALU6:

        if ((pLoCon = getLoCon(pPhSeg->NAME)) == (locon_list*)NULL) {
          wprinth((char*)NULL);
          wprintf(
            "\n  Physical terminal \"%s\" doesn't match any ", pPhSeg->NAME);
          wprints("logical terminal.\n");

          continue;
        }

        tCALU = (eGrid_t*)NULL;
        phseg2TGrid(&tCALU, pPhSeg);

        if ((pPIN = getPIN(LV_pMACRO, pPhSeg->NAME)) == (ePIN_t*)NULL) {

          m_AddPin(LV_pMACRO->lPIN, pPhSeg->NAME);
          LV_pMACRO->lPIN->DIRECTION = MBK2DEF_locondir(pLoCon);
          if (isck(pPhSeg->NAME))
            LV_pMACRO->lPIN->USE = C_USE_CLOCK;

          pPIN = LV_pMACRO->lPIN;
        }

        m_AddPort(pPIN->lPORT, C_PORTITEM_LAYER, (long)pPhSeg->LAYER);
        TGrid2PORT(&(pPIN->lPORT), tCALU);

        break;
    }
  }
}
