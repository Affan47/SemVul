ProcessHandler()
{
  cmGeneratedFileStream ofs;
  if ( !this->CTest->OpenOutputFile(this->CTest->GetCurrentTag(),
                                    "Upload.xml", ofs))
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE,
      "Cannot open Upload.xml file" << std::endl);
    return -1;
    }

  cmCTest::SetOfStrings::const_iterator it;
  ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
     << "<?xml-stylesheet type=\"text/xsl\" "
    "href=\"Dart/Source/Server/XSL/Build.xsl "
    "<file:///Dart/Source/Server/XSL/Build.xsl> \"?>\n"
     << "<Site BuildName=\""
     << this->CTest->GetCTestConfiguration("BuildName")
     << "\" BuildStamp=\""
     << this->CTest->GetCurrentTag() << "-"
     << this->CTest->GetTestModelString() << "\" Name=\""
     << this->CTest->GetCTestConfiguration("Site") << "\" Generator=\"ctest"
     << cmVersion::GetCMakeVersion()
     << "\">\n";
  this->CTest->AddSiteProperties(ofs);
  ofs << "<Upload>\n";

  for ( it = this->Files.begin(); it != this->Files.end(); it ++ )
    {
    cmCTestLog(this->CTest, OUTPUT,
               "\tUpload file: " << it->c_str() << std::endl);
    ofs << "<File filename=\"" << cmXMLSafe(*it) << "\">\n"
       << "<Content encoding=\"base64\">\n";
    ofs << this->CTest->Base64EncodeFile(*it);
    ofs << "\n</Content>\n"
      << "</File>\n";
    }
  ofs << "</Upload>\n"
    << "</Site>\n";
  return 0;
}
