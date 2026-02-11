GetPropertiesDocumentation(std::map<std::string,
                             cmDocumentationSection *>& v) const
{
  for(cmPropertyDefinitionMap::const_iterator j = this->begin();
      j != this->end(); ++j)
    {

    std::string secName = j->second.GetDocumentationSection();

    if (!secName.size())
      {
      switch (j->second.GetScope())
        {
        case cmProperty::GLOBAL:
          secName = "Properties of Global Scope";
          break;
        case cmProperty::TARGET:
          secName = "Properties on Targets";
          break;
        case cmProperty::SOURCE_FILE:
          secName = "Properties on Source Files";
          break;
        case cmProperty::DIRECTORY:
          secName = "Properties on Directories";
          break;
        case cmProperty::TEST:
          secName = "Properties on Tests";
          break;
        case cmProperty::VARIABLE:
          secName = "Variables";
          break;
        case cmProperty::CACHED_VARIABLE:
          secName = "Cached Variables";
          break;
        default:
          secName = "Properties of Unknown Scope";
          break;
        }
      }
    if (!v[secName])
      {
      v[secName] = new
        cmDocumentationSection(secName.c_str(),
                               cmSystemTools::UpperCase(secName).c_str());
      }
    cmDocumentationEntry e = j->second.GetDocumentation();
    if (e.Brief.size() || e.Full.size())
      {
      v[secName]->Append(e);
      }
    }
}
