flush()
{
  if (status_.good() && current_)
  {

    if (outputBufCount_ == DCMZLIBOUTPUTFILTER_BUFSIZE) flushOutputBuffer();


    while (status_.good() && inputBufCount_ > 0 && outputBufCount_ < DCMZLIBOUTPUTFILTER_BUFSIZE)
    {
      compressInputBuffer(OFTrue);
      if (outputBufCount_ == DCMZLIBOUTPUTFILTER_BUFSIZE) flushOutputBuffer();
    }

    while (status_.good() && (! flushed_) && outputBufCount_ < DCMZLIBOUTPUTFILTER_BUFSIZE)
    {

      compress(NULL, 0, OFTrue);
      if (outputBufCount_ == DCMZLIBOUTPUTFILTER_BUFSIZE) flushOutputBuffer();
    }


    if (outputBufCount_ > 0) flushOutputBuffer();
  }
}
