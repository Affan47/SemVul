GenerateXML(std::ostream &sout)
{
  std::string EOL(" \\");

  sout << "#define GENERATE_XML \\" << std::endl;

  sout << "  if (argc >= 2 && (strcmp(argv[1],\"--xml\") == 0))" << EOL << std::endl;
  sout << "    {" << EOL << std::endl;
  sout << "    std::cout << GetXMLModuleDescription();" << EOL << std::endl;
  sout << "    return EXIT_SUCCESS;" << EOL << std::endl;
  sout << "    }" << std::endl;
}
