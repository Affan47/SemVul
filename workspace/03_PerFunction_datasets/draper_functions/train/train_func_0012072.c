SearchServer(std::vector<std::string> tokens)
{
  std::vector<mdo::Object*> results;
  SearchXMLParser parser;
  parser.SetObject(&results);
  mws::WebAPI::Instance()->GetRestAPI()->SetXMLParser(&parser);

  std::string fields = "midas.resources.search?search=";

  bool space = false;
  for(std::vector<std::string>::iterator i = tokens.begin();
      i != tokens.end(); ++i)
    {
    fields += midasUtils::EscapeForURL(*i);
    if(space)
      {
      fields += midasUtils::EscapeForURL(" ");
      }
    space = true;
    }
  mws::WebAPI::Instance()->Execute(fields.c_str());
  return results;
}
