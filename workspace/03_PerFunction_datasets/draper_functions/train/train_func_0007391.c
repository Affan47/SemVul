addPow(applPow, aY, aW, aName, aType, aDir)
  ePow_t **applPow;
    long   aY;
    long   aW;
    char  *aName;
    char   aType;
    char   aDir;
{
  ePow_t *pPow, **ppPow;


  pPow        = (ePow_t*)mbkalloc(sizeof(ePow_t));
  pPow->y     = aY;
  pPow->w     = aW;
  pPow->flags = 0;
  pPow->inter = NULL;

  switch(aDir) {
    case C_POWER_VERTICAL:
      pPow->xMin = LV_YAB1;
      pPow->xMax = LV_YAB2;
      pPow->min  = LV_YAB2;
      pPow->max  = LV_YAB1;
      break;
    default:
    case C_POWER_HORIZONTAL:
      pPow->xMin = LV_XAB1;
      pPow->xMax = LV_XAB2;
      pPow->min  = LV_XAB2;
      pPow->max  = LV_XAB1;
      break;
  }

  pPow->Name = namealloc(aName);
  pPow->Type = aType;


  for(ppPow = applPow ; *ppPow != NULL ; ppPow = &((*ppPow)->Next)) {
    if ((*ppPow)->y >= pPow->y) {
      pPow->Next = *ppPow;
      *ppPow = pPow;
      break;
    }
  }


  if (*ppPow == (ePow_t*)NULL) {
    pPow->Next = *ppPow;
    *ppPow = pPow;
  }


  return(pPow);
}
