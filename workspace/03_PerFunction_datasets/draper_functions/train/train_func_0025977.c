WriteTestResultFooter(std::ostream& os,
                                               cmCTestTestResult* result)
{
  if(!result->Properties->Labels.empty())
    {
    os << "\t\t<Labels>\n";
    std::vector<std::string> const& labels = result->Properties->Labels;
    for(std::vector<std::string>::const_iterator li = labels.begin();
        li != labels.end(); ++li)
      {
      os << "\t\t\t<Label>" << cmXMLSafe(*li) << "</Label>\n";
      }
    os << "\t\t</Labels>\n";
    }

  os
    << "\t</Test>" << std::endl;
}
