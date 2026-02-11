IsValid(istream& InputStream)
{
  bool returnBool = true;

  istream::pos_type StreamPos = InputStream.tellg();

  try
    {
    testIterator junk;
    this->ToUnicode(InputStream, junk);
    }
  catch(...)
    {
    returnBool = false;
    }


  InputStream.clear();
  InputStream.seekg(StreamPos);

  return returnBool;
}
