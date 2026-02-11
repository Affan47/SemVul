GetValue(const char* tag,
                                  bool& value,
                                  std::ifstream& fin)
{
  std::string line;
  cmSystemTools::GetLineFromStream(fin, line);
  bool ret = true;
  if(line == tag)
    {
#ifdef __HAIKU__
    int tmp = 0;
    fin >> tmp;
    value = false;
    if(tmp)
      {
      value = true;
      }
#else
    fin >> value;
#endif
    ret = cmSystemTools::GetLineFromStream(fin, line);
    }
  else
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE,
               "parse error: missing tag: "
               << tag << " found [" << line << "]" << std::endl);
    ret = false;
    }
  return ret;
}
