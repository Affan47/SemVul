parseRoleSelectionItems(
  DcmAssociationConfiguration& cfg,
  OFConfigFile& config)
{
  OFCondition result = EC_Normal;

  config.set_section(2, L2_SCPSCUROLESELECTION);
  if (! config.section_valid(2)) return result;

  char buf[64];
  unsigned int counter;
  OFBool found;
  const char *key = NULL;
  const char *value = NULL;
  OFString abstractSyntaxUID;
  OFString roleKey;
  size_t separator = 0;
  size_t i;
  size_t len;
  char c;

  config.first_section(1);
  while (config.section_valid(1))
  {
    key = config.get_keyword(1);
    counter = 0;
    found = OFTrue;
    while (found)
    {
      sprintf(buf, "%s%u", L0_ROLE_X, ++counter);
      value = config.get_entry(buf);
      if (value)
      {

        abstractSyntaxUID = value;
        len = abstractSyntaxUID.size();
        separator = abstractSyntaxUID.find("\\");
        if (separator == OFString_npos)
        {
          OFString s("syntax error: missing '\\' in entry ");
          s += buf;
          s += " in config file";
          return makeOFCondition(OFM_dcmnet, 1054, OF_error, s.c_str());
        }


        roleKey.clear();
        i = separator;
        while (++i < len)
        {
          c = abstractSyntaxUID.at(i);
          roleKey += (char) (toupper(TO_UCHAR(c)));
        }


        abstractSyntaxUID.erase(separator);


        if (roleKey == "SCU")
        {
          result = cfg.addRole(key, abstractSyntaxUID.c_str(), ASC_SC_ROLE_SCU);
        }
        else if (roleKey == "SCP")
        {
          result = cfg.addRole(key, abstractSyntaxUID.c_str(), ASC_SC_ROLE_SCP);
        }
        else if (roleKey == "BOTH")
        {
          result = cfg.addRole(key, abstractSyntaxUID.c_str(), ASC_SC_ROLE_SCUSCP);
        }
        else
        {
          OFString s("syntax error: unknown role key in entry ");
          s += buf;
          s += " in config file";
          result = makeOFCondition(OFM_dcmnet, 1055, OF_error, s.c_str());
        }

        if (result.bad()) return result;

      } else found = OFFalse;
    }
    config.next_section(1);
  }

  return result;
}
