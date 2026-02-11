checkRowNames() {

  int i, nrow = getNumRows();

  if(numberHash_[0] != nrow+1) {
    setDefaultRowNames();
    handler_->message(COIN_GENERAL_WARNING,messages_)<<
      "### CoinLpIO::checkRowNames(): non distinct or missing row names or objective function name.\nNow using default row names."
						     <<CoinMessageEol;
  }

  char const * const * rowNames = getRowNames();
  const char *rSense = getRowSense();
  char rName[256];


  for(i=0; i<nrow; i++) {
    if(rSense[i] == 'R') {
      sprintf(rName, "%s_low", rowNames[i]);
      if(findHash(rName, 0) != -1) {
	setDefaultRowNames();
	char printBuffer[512];
	sprintf(printBuffer,"### CoinLpIO::checkRowNames(): ranged constraint %d has a name %s identical to another constraint name or objective function name.\nUse getPreviousNames() to get the old row names.\nNow using default row names.", i, rName);
	handler_->message(COIN_GENERAL_WARNING,messages_)<<printBuffer
						  <<CoinMessageEol;
	break;
      }
    }
  }
}
