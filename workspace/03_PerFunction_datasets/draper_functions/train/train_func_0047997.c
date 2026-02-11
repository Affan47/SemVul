testXMLParser(int, char*[])
{

  cmXMLParser parser;
  if(!parser.ParseFile(SOURCE_DIR "/testXMLParser.xml"))
    {
    cmsys_ios::cerr << "cmXMLParser failed!" << cmsys_ios::endl;
    return 1;
    }
  return 0;
}
