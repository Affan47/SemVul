main(int argc, char* argv[])
{


  std::locale::global(std::locale(""));

  std::string schemafilepath("example.xsd"),
              docfilepath("example.xml");

  if(argc!=0 && argc!=3)
    std::cout << "usage : " << argv[0] << " [document schema]" << std::endl;
  else
  {
    if(argc == 3)
    {
      docfilepath = argv[1];
      schemafilepath = argv[2];
    }

    try
    {
      xmlpp::DomParser       parser(docfilepath);
      xmlpp::SchemaValidator validator(schemafilepath);

      try
      {
        validator.validate( parser.get_document() );
        std::cout << "Valid document" << std::endl;
      }
      catch( const xmlpp::validity_error& error)
      {
#ifdef LIBXMLCPP_EXCEPTIONS_ENABLED
        std::cout << "Error validating the document" << std::endl;
        std::cout << error.what();
#endif
      }
    }
    catch( const xmlpp::parse_error& )
    {
      std::cerr << "Error parsing the schema" << std::endl;
    }
  }
}
