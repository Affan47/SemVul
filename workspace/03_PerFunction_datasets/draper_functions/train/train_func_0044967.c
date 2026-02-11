instance2obs(apIns)
  struct phins *apIns;
{
  struct phfig *pFig;
  struct phseg *pSeg, flatSeg;
# if 0
  struct phvia *pVIA, flatVIA;
          char *viaName = STRING_OBSTACLE;
# endif


  pFig = getphfig (apIns->FIGNAME, 'A');

  for (pSeg = pFig->PHSEG; pSeg != NULL; pSeg = pSeg->NEXT) {
    if (  isvdd (pSeg->NAME ) ||  isvss (pSeg->NAME )) continue;
    if (!isCALU (pSeg->LAYER) && !isobs (pSeg))        continue;


    xyflatseg (&flatSeg, pSeg,
               apIns->XINS, apIns->YINS,
                pFig->XAB1,  pFig->YAB1,
                pFig->XAB2,  pFig->YAB2,
               apIns->TRANSF);

    seg2obs (&flatSeg);
  }

# if 0
  for (pVIA = pFig->PHVIA; pVIA != NULL; pVIA = pVIA->NEXT) {
    if (isvdd (pVIA->NAME) || isvss (pVIA->NAME)) continue;

    xyflatvia (&flatVIA, pVIA,
               apIns->XINS, apIns->YINS,
                pFig->XAB1,  pFig->YAB1,
                pFig->XAB2,  pFig->YAB2,
               apIns->TRANSF);

    flatVIA.NAME = (pVIA->NAME != NULL) ? pVIA->NAME : viaName;

    via2obs (&flatVIA);
  }
# endif
}
