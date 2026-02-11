FindInlineDataPosition(OffsetType start)
{

  char c=0;
  this->SeekG(start);
  while(this->Stream->get(c) && (c != '>'))
    {
    ;
    }
  while(this->Stream->get(c) && this->IsSpace(c))
    {
    ;
    }


  if(c == '<') { return 0; }
  OffsetType pos = this->TellG();
  return (pos-1);
}
