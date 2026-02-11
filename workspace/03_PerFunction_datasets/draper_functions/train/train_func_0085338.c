ExtractValueFromCpuInfoFile(kwsys_stl::string buffer,const char* word,size_t init)
{
  size_t pos = buffer.find(word,init);
  if(pos != buffer.npos)
    {
    this->CurrentPositionInFile = pos;
    pos = buffer.find(":",pos);
    size_t pos2 = buffer.find("\n",pos);
    if(pos!=buffer.npos && pos2!=buffer.npos)
      {
      return buffer.substr(pos+2,pos2-pos-2);
      }
    }
  this->CurrentPositionInFile = buffer.npos;
  return "";
}
