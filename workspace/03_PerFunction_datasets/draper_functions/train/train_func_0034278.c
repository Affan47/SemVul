GetHeaderInfo(std::istream &is, TransferSyntax &ts)
{

  is.seekg( 0, std::ios::end);
  size_t buf_size = (size_t)is.tellg();
  char *dummy_buffer = new char[buf_size];
  is.seekg(0, std::ios::beg);
  is.read( dummy_buffer, buf_size);
  bool b = GetHeaderInfo( dummy_buffer, (size_t)buf_size, ts );
  delete[] dummy_buffer;
  return b;
}
