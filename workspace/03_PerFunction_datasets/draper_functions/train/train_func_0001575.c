create(void const * const buf,const unsigned int size,
    const EncodeType encodetype, const GUTF8String &encoding)
{
  return encoding.length()
    ?create(buf,size,encodetype)
    :create(buf,size,encoding);
}
