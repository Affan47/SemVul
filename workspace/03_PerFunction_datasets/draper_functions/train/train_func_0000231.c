DoPlanarConfiguration(std::istream &is, std::ostream &os)
{

  std::streampos start = is.tellg();
  assert( 0 - start == 0 );
  is.seekg( 0, std::ios::end);
  size_t buf_size = (size_t)is.tellg();

  char *dummy_buffer = new char[(unsigned int)buf_size];
  is.seekg(start, std::ios::beg);
  is.read( dummy_buffer, buf_size);
  is.seekg(start, std::ios::beg);


  assert( buf_size % 3 == 0 );
  unsigned long size = (unsigned long)buf_size/3;
  char *copy = new char[ (unsigned int)buf_size ];


  const char *r = dummy_buffer ;
  const char *g = dummy_buffer  + size;
  const char *b = dummy_buffer  + size + size;

  char *p = copy ;
  for (unsigned long j = 0; j < size; ++j)
    {
    *(p++) = *(r++);
    *(p++) = *(g++);
    *(p++) = *(b++);
    }
  delete[] dummy_buffer ;

  os.write(copy , buf_size);
  delete[] copy;
  return true;
}
