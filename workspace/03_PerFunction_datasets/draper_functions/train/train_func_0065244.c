CompressOutput()
{
  int ret;
  z_stream strm;

  unsigned char* in =
    reinterpret_cast<unsigned char*>(
    const_cast<char*>(this->ProcessOutput.c_str()));

  int outSize = static_cast<int>(this->ProcessOutput.size() * 1.001 + 13);
  unsigned char* out = new unsigned char[outSize];

  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;
  ret = deflateInit(&strm, -1);
  if (ret != Z_OK)
    {
    return;
    }

  strm.avail_in = static_cast<uInt>(this->ProcessOutput.size());
  strm.next_in = in;
  strm.avail_out = outSize;
  strm.next_out = out;
  ret = deflate(&strm, Z_FINISH);

  if(ret == Z_STREAM_ERROR || ret != Z_STREAM_END)
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE, "Error during output "
      "compression. Sending uncompressed output." << std::endl);
    return;
    }

  (void)deflateEnd(&strm);

  unsigned char *encoded_buffer
    = new unsigned char[static_cast<int>(outSize * 1.5)];

  unsigned long rlen
    = cmsysBase64_Encode(out, strm.total_out, encoded_buffer, 1);

  for(unsigned long i = 0; i < rlen; i++)
    {
    this->CompressedOutput += encoded_buffer[i];
    }

  if(strm.total_in)
    {
    this->CompressionRatio = static_cast<double>(strm.total_out) /
                             static_cast<double>(strm.total_in);
    }

  delete [] encoded_buffer;
  delete [] out;
}
