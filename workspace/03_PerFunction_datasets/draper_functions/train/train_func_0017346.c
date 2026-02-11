init(GP<ByteStream> gbs, const bool striped)
{
  rowsperstrip = (striped ? gbs->read16() : height);
  src = VLSource::create(gbs, striped);
  mrtable = VLTable::create(mrcodes, 7);
  btable = VLTable::create(bcodes, 13);
  wtable = VLTable::create(wcodes, 13);
}
