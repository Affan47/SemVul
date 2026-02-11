create(GP<ByteStream> xbs)
{
  BSByteStream::Decode *rbs=new BSByteStream::Decode(xbs);
  GP<ByteStream> retval=rbs;
  rbs->init();
  return retval;
}
