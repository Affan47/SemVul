finish()
{

  if (printStatus_ < 3 && messageOut_ != messageBuffer_) {
    internalPrint();
  }

  internalNumber_ = -1 ;
  format_ = NULL ;
  messageBuffer_[0] = '\0' ;
  messageOut_ = messageBuffer_ ;
  printStatus_ = 0 ;
  doubleValue_.clear() ;
  longValue_.clear() ;
  charValue_.clear() ;
  stringValue_.clear() ;
  return (0) ;
}
