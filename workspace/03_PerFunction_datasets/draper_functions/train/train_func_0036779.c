def_net_start(char *name)
{
  struct authelem *pElem;


  LV_numObjectsRead++;
  LV_modelName = DEF2MBK_name (name);

  mprintf2 ("     - \"%s\"\n", LV_modelName);

  if ((pElem = searchauthelem (LV_htPin, LV_modelName)) != NULL) {


    LV_flags     = F_SEG_PIN;
    if (LV_pLoFig) {
      LV_pLoSig = getlosig (LV_pLoFig, pElem->VALUE);
    }
  } else {


    if (LV_pLoFig) {
      LV_pLoSig = addlosig (LV_pLoFig,
                            LV_mSig++,
                            addchain (NULL, (void*)LV_modelName),
                            INTERNAL);
    }
    LV_flags  = 0L;
  }

  free (name);
}
