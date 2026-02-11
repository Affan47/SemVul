toString(IOP::IOR& ior)
{
  cdrMemoryStream buf(CORBA::ULong(0),CORBA::Boolean(1));
  buf.marshalBoolean(omni::myByteOrder);
  buf.marshalRawString(ior.type_id);
  ior.profiles >>= buf;


  buf.rewindInputPtr();
  size_t s = buf.bufSize();
  CORBA::Char * data = (CORBA::Char *)buf.bufPtr();

  char *result = new char[4+s*2+1];
  result[4+s*2] = '\0';
  result[0] = 'I';
  result[1] = 'O';
  result[2] = 'R';
  result[3] = ':';
  for (int i=0; i < (int)s; i++) {
    int j = 4 + i*2;
    int v = (data[i] & 0xf0);
    v = v >> 4;
    if (v < 10)
      result[j] = '0' + v;
    else
      result[j] = 'a' + (v - 10);
    v = ((data[i] & 0xf));
    if (v < 10)
      result[j+1] = '0' + v;
    else
      result[j+1] = 'a' + (v - 10);
  }
  return result;
}
