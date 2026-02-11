compressInputBuffer(OFBool finalize)
{
  if (inputBufCount_ || finalize)
  {

    offile_off_t numBytes = (inputBufStart_ + inputBufCount_ > DCMZLIBOUTPUTFILTER_BUFSIZE) ?
      (DCMZLIBOUTPUTFILTER_BUFSIZE - inputBufStart_) : inputBufCount_ ;

    offile_off_t written = compress(inputBuf_ + inputBufStart_, numBytes, finalize);


    inputBufCount_ -= written;
    inputBufStart_ += written;

    if (inputBufStart_ == DCMZLIBOUTPUTFILTER_BUFSIZE)
    {

      inputBufStart_ = 0;


      if (inputBufCount_ && written)
      {
        written = compress(inputBuf_, inputBufCount_, finalize);


        inputBufCount_ -= written;
        inputBufStart_ += written;
      }
    }


    if (inputBufCount_ == 0) inputBufStart_ = 0;
  }
}
