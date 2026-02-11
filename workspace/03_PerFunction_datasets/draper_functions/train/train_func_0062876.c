reserve_buffer_space(long int bytes)
{
  if (bytes > static_cast<long int>(iobuf_size_rep)) {
    if (iobuf_uchar_repp != 0) {
      delete[] iobuf_uchar_repp;
      iobuf_uchar_repp = 0;
    }


    iobuf_uchar_repp = new unsigned char [bytes];
    iobuf_size_rep = bytes;
  }
}
