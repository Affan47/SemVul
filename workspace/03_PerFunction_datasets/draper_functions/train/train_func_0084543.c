internalPrint()
{
  int returnCode=0;
  if (messageOut_>messageBuffer_) {
    *messageOut_=0;

    messageOut_--;
    while (messageOut_>=messageBuffer_) {
      if (*messageOut_==' '||*messageOut_==',') {
	*messageOut_=0;
	messageOut_--;
      } else {
	break;
      }
    }

    returnCode=print();

    checkSeverity();
  }
  return returnCode;
}
