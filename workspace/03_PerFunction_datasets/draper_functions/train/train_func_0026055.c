gutsOfDelete()
{
  if (numberObjects_ > 0) {
    numberObjects_ = 0;
    numberBeforeTrusted_ = 0;
    delete[] upTotalChange_;   upTotalChange_ = NULL;
    delete[] downTotalChange_; downTotalChange_ = NULL;
    delete[] upNumber_;        upNumber_ = NULL;
    delete[] downNumber_;      downNumber_ = NULL;
  }
}
