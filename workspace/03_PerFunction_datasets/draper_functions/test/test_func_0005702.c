parseFields(const ByteVector &data)
{


  if(data.size() < 2)
    return;


  d->textEncoding = String::Type(data[0]);


  int byteAlign = d->textEncoding == String::Latin1 || d->textEncoding == String::UTF8 ? 1 : 2;


  int dataLength = data.size() - 1;

  while(dataLength > 0 && data[dataLength] == 0)
    dataLength--;

  while(dataLength % byteAlign != 0)
    dataLength++;

  ByteVectorList l = ByteVectorList::split(data.mid(1, dataLength), textDelimiter(d->textEncoding), byteAlign);

  d->fieldList.clear();


  for(ByteVectorList::Iterator it = l.begin(); it != l.end(); it++) {
    if(!(*it).isEmpty()) {
      String s(*it, d->textEncoding);
      d->fieldList.append(s);
    }
  }
}
