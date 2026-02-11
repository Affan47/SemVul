main ()
{
  std::ifstream file("compile_commands.json");
  CompileCommandParser parser(&file);
  parser.Parse();
  for(CompileCommandParser::TranslationUnitsType::const_iterator
      it = parser.GetTranslationUnits().begin(),
      end = parser.GetTranslationUnits().end(); it != end; ++it)
    {
    std::vector<cmStdString> command;
    cmSystemTools::ParseUnixCommandLine(it->at("command").c_str(), command);
    if (!cmSystemTools::RunSingleCommand(
            command, 0, 0, it->at("directory").c_str()))
      {
      std::cout << "ERROR: Failed to run command \""
                << command[0] << "\"" << std::endl;
      exit(1);
      }
    }
  return 0;
}
