sortPINS()
{
  ePIN_t *pPIN, *pTmp, **ppHead;
  ePIN_t *pHeadINOUT , *pTailINOUT;
  ePIN_t *pHeadOUTPUT, *pTailOUTPUT;
  ePIN_t *pHeadINPUT , *pTailINPUT;
  ePIN_t *pHeadPOWER , *pTailPOWER;
  ePIN_t *pHeadCLOCK , *pTailCLOCK;


  pHeadINOUT  = pTailINOUT  = (ePIN_t*)NULL;
  pHeadOUTPUT = pTailOUTPUT = (ePIN_t*)NULL;
  pHeadINPUT  = pTailINPUT  = (ePIN_t*)NULL;
  pHeadPOWER  = pTailPOWER  = (ePIN_t*)NULL;
  pHeadCLOCK  = pTailCLOCK  = (ePIN_t*)NULL;

  for(pPIN = LV_pMACRO->lPIN; pPIN != (ePIN_t*)NULL;) {
    pTmp = pPIN;
    pPIN = pPIN->Next;

    switch(pTmp->USE) {
      case C_USE_POWER:
      case C_USE_GROUND:
        insertPIN(&pHeadPOWER, &pTailPOWER, pTmp);
        continue;
      case C_USE_CLOCK:
	insertPIN(&pHeadCLOCK, &pTailCLOCK, pTmp);
	continue;
    }

    switch(pTmp->DIRECTION) {
      case C_DIRECTION_INPUT:
        insertPIN(&pHeadINPUT, &pTailINPUT, pTmp);
        continue;
      case C_DIRECTION_OUTPUT:
      case C_DIRECTION_TRISTATE:
        insertPIN(&pHeadOUTPUT, &pTailOUTPUT, pTmp);
        continue;
      case C_DIRECTION_INOUT:
      case C_DIRECTION_FEEDTHRU:
        insertPIN(&pHeadINOUT, &pTailINOUT, pTmp);
        continue;
    }

    eprinth((char*)NULL);
    eprintf("\n  Pin \"%s\" have no DIRECTION!?\n", pTmp->pinName);
    EXIT(1);
  }


  ppHead = &(LV_pMACRO->lPIN);

  if (pHeadINOUT != (ePIN_t*)NULL) {
    *ppHead = pHeadINOUT;   ppHead = &(pTailINOUT->Next);
  }

  if (pHeadOUTPUT != (ePIN_t*)NULL) {
    *ppHead = pHeadOUTPUT; ppHead = &(pTailOUTPUT->Next);
  }

  if (pHeadINPUT != (ePIN_t*)NULL) {
    *ppHead = pHeadINPUT;  ppHead = &(pTailINPUT->Next);
  }

  if (pHeadPOWER != (ePIN_t*)NULL) {
    *ppHead = pHeadPOWER;  ppHead = &(pTailPOWER->Next);
  }

  if (pHeadCLOCK != (ePIN_t*)NULL) {
    *ppHead = pHeadCLOCK;  ppHead = &(pTailCLOCK->Next);
  }

  *ppHead = (ePIN_t*)NULL;
}
