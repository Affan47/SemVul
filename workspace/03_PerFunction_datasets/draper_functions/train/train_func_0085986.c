main(int argc, char **argv) {
  LC_CLIENT *cl;
  LC_CARD *card=0;
  LC_CLIENT_RESULT res;

  cl=LC_Client_new("tutorial1c", "1.0");
  res=LC_Client_Init(cl);
  if (res!=LC_Client_ResultOk) {
    showError(card, res, "Init");
    LC_Client_free(cl);
    return 1;
  }

  fprintf(stderr, "INFO: Connecting to server.\n");
  res=LC_Client_Start(cl);
  if (res!=LC_Client_ResultOk) {
    showError(card, res, "StartWait");
    LC_Client_free(cl);
    return 2;
  }

  fprintf(stderr, "Please insert a chip card.\n");
  res=LC_Client_GetNextCard(cl, &card, 30);
  if (res!=LC_Client_ResultOk) {
    showError(card, res, "GetNextCard");
    LC_Client_Stop(cl);
    LC_Client_free(cl);
    return 2;
  }


  fprintf(stderr, "INFO: Telling the server that we need no more cards.\n");
  res=LC_Client_Stop(cl);
  if (res!=LC_Client_ResultOk) {
    showError(card, res, "Stop");
    LC_Client_ReleaseCard(cl, card);
    LC_Card_free(card);
    LC_Client_free(cl);
    return 2;
  }


  fprintf(stderr, "INFO: Opening card.\n");
  res=LC_Card_Open(card);
  if (res!=LC_Client_ResultOk) {
    showError(card, res, "CardOpen");
    LC_Client_ReleaseCard(cl, card);
    LC_Card_free(card);
    LC_Client_free(cl);
    return 2;
  }


  fprintf(stderr, "INFO: I got this card:\n");
  LC_Card_Dump(card, 0);


  fprintf(stderr, "INFO: Closing card.\n");
  res=LC_Card_Close(card);
  if (res!=LC_Client_ResultOk) {
    showError(card, res, "CardClose");
    LC_Client_ReleaseCard(cl, card);
    LC_Card_free(card);
    LC_Client_free(cl);
    return 2;
  }
  fprintf(stderr, "INFO: Card closed.\n");


  res=LC_Client_ReleaseCard(cl, card);
  if (res!=LC_Client_ResultOk) {
    showError(card, res, "CardRelease");
    LC_Card_free(card);
    LC_Client_free(cl);
    return 2;
  }


  LC_Card_free(card);
  LC_Client_free(cl);
  return 0;
}
