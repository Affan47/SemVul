testXMLSafe(int, char*[])
{
  int result = 0;
  for(test_pair const* p = pairs; p->in; ++p)
    {
    cmXMLSafe xs(p->in);
    cmOStringStream oss;
    oss << xs;
    std::string out = oss.str();
    if(out != p->out)
      {
      printf("expected [%s], got [%s]\n", p->out, out.c_str());
      result = 1;
      }
    }
  return result;
}
