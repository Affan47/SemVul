HashFile(const char* file)
{
  std::ifstream fin(file, std::ios::in | cmsys_ios_binary);
  if(!fin)
    {
    return "";
    }

  this->Initialize();


  const int bufferSize = 4096;
  char buffer[bufferSize];
  unsigned char const* buffer_uc =
    reinterpret_cast<unsigned char const*>(buffer);


  while(fin)
    {
    fin.read(buffer, bufferSize);
    if(int gcount = static_cast<int>(fin.gcount()))
      {
      this->Append(buffer_uc, gcount);
      }
    }
  if(fin.eof())
    {
    return this->Finalize();
    }
  return "";
}
