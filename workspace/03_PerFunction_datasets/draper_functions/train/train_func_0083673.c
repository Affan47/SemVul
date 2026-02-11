callback(const MSSymbol& name_)
{
  CallbackNode *node=callbackNode(name_);
  return (node!=0)?node->_pCallback:0;
}
