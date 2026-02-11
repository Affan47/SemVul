skip(offile_off_t skiplen)
{
  if (status_.bad() || (current_ == NULL)) return 0;
  offile_off_t offset = 0;
  offile_off_t availBytes = 0;
  offile_off_t result = 0;
  do
  {

    if (outputBufCount_)
    {

      offset = outputBufStart_ + outputBufPutback_;
      if (offset >= DCMZLIBINPUTFILTER_BUFSIZE) offset -= DCMZLIBINPUTFILTER_BUFSIZE;

      availBytes = outputBufCount_;
      if (offset + availBytes > DCMZLIBINPUTFILTER_BUFSIZE) availBytes = DCMZLIBINPUTFILTER_BUFSIZE - offset;
      if (availBytes > skiplen) availBytes = skiplen;
      result += availBytes;
      skiplen -= availBytes;


      outputBufPutback_ += availBytes;
      outputBufCount_ -= availBytes;
      if (outputBufPutback_ > DCMZLIBINPUTFILTER_PUTBACKSIZE)
      {
        outputBufStart_ += outputBufPutback_ - DCMZLIBINPUTFILTER_PUTBACKSIZE;
        outputBufPutback_ = DCMZLIBINPUTFILTER_PUTBACKSIZE;
        if (outputBufStart_ >= DCMZLIBINPUTFILTER_BUFSIZE) outputBufStart_ -= DCMZLIBINPUTFILTER_BUFSIZE;
      }
    }


    fillOutputBuffer();
  } while (skiplen && outputBufCount_);


  return result;
}
