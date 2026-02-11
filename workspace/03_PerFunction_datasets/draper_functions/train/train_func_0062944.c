message (int messageNumber,
			     const CoinMessages &normalMessages)
{

  if (messageOut_ != messageBuffer_) {
    internalPrint() ;
  }

  internalNumber_ = messageNumber ;
  currentMessage_ = *(normalMessages.message_[messageNumber]) ;
  source_ = normalMessages.source_ ;
  format_ = currentMessage_.message_ ;
  highestNumber_ = CoinMax(highestNumber_,currentMessage_.externalNumber_);


  messageBuffer_[0] = '\0' ;
  messageOut_ = messageBuffer_ ;


  calcPrintStatus(currentMessage_.detail_,normalMessages.class_) ;


  if (!printStatus_) {
    if (prefix_) {
      sprintf(messageOut_,"%s%4.4d%c ",source_.c_str(),
	      currentMessage_.externalNumber_,
	      currentMessage_.severity_) ;
      messageOut_ += strlen(messageOut_) ;
    }
    format_ = nextPerCent(format_,true) ;
  }
  return (*this) ;
}
