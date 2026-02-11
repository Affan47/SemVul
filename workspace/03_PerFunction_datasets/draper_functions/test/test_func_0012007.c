checkLofig(apLofig)
  struct lofig *apLofig;
{
  struct loins *pIns;
  struct locon *pCon;
          long  unassigned;


  unassigned = 0;

  for (pIns = apLofig->LOINS; pIns != NULL; pIns = pIns->NEXT) {
    for(pCon = pIns->LOCON; pCon != NULL; pCon = pCon->NEXT) {
      if (!pCon->SIG) {
        unassigned++;

        warnMBK ("defloadlophfig");
        wprintf ("Terminal %s of instance %s is not assigned.\n",
                 pCon->NAME, pIns->INSNAME);
      }
    }
  }

  if (unassigned) {
    errMBK  ("defloadlophig");
    eprintf ("There is %ld terminals unassigned.\n", unassigned);
    EXIT (1);
  }
}
