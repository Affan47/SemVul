AH_HHD14_AddChallengeParams_09(AH_JOB *j,
                                   const AB_VALUE *vAmount,
                                   const char *sRemoteIban) {

  if (vAmount) {
    GWEN_BUFFER *tbuf;

    tbuf=GWEN_Buffer_new(0, 64, 0, 1);
    AH_Job_ValueToChallengeString(vAmount, tbuf);
    AH_Job_AddChallengeParam(j, GWEN_Buffer_GetStart(tbuf));
    GWEN_Buffer_free(tbuf);
  }


  if (sRemoteIban && *sRemoteIban)
    AH_Job_AddChallengeParam(j, sRemoteIban);
  else {
    DBG_ERROR(AQHBCI_LOGDOMAIN, "No remote iban");
    return GWEN_ERROR_INVALID;
  }


  return 0;
}
