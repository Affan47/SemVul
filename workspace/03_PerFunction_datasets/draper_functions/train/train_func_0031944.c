skip(offile_off_t skiplen)
{
  offile_off_t result = 0;
  if (status_.good() && file_.open() && skiplen)
  {
    offile_off_t pos = file_.ftell();
    result = (size_ - pos < skiplen) ? (size_ - pos) : skiplen;
    if (file_.fseek(result, SEEK_CUR))
    {
      OFString s("(unknown error code)");
      file_.getLastErrorString(s);
      status_ = makeOFCondition(OFM_dcmdata, 18, OF_error, s.c_str());
    }
  }
  return result;
}
