copyPrimary(const char *data_,int itemCount_)
{
  if (ownSelection(XA_PRIMARY)==MSSuccess)
   {
     MSString aString(data_,itemCount_);
     _server->copyBuffer(aString);
     return MSSuccess;
   }
  return MSFailure;
}
