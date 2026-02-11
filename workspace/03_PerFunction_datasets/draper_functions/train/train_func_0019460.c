OpenRulesFileStream()
{

  std::string rulesFilePath =
    this->GetCMakeInstance()->GetHomeOutputDirectory();
  rulesFilePath += "/";
  rulesFilePath += cmGlobalNinjaGenerator::NINJA_RULES_FILE;


  if (!this->RulesFileStream)
    {
    this->RulesFileStream = new cmGeneratedFileStream(rulesFilePath.c_str());
    if (!this->RulesFileStream)
      {


      return;
      }
    }


  this->WriteDisclaimer(*this->RulesFileStream);


  *this->RulesFileStream
    << "# This file contains all the rules used to get the outputs files\n"
    << "# built from the input files.\n"
    << "# It is included in the main '" << NINJA_BUILD_FILE << "'.\n\n"
    ;
}
