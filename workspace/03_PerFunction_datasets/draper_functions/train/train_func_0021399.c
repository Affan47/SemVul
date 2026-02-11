propertyToString(Atom target_,char *data_,int itemCount_)
{
  if (target_==XA_ATOM) atomsFromData(data_,itemCount_);
  else if (target_==XA_STRING)
   {
     MSString aString(data_,itemCount_);
     _server->pasteBuffer(aString);
   }
}
