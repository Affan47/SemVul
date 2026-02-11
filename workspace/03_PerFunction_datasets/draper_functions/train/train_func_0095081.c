GenerateXMLLaunchedFragment(std::ostream& os,
                                                      const char* fname)
{
  std::ifstream fin(fname, std::ios::in | std::ios::binary);
  std::string line;
  while(cmSystemTools::GetLineFromStream(fin, line))
    {
    os << line << "\n";
    }
}
