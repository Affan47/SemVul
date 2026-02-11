main(int argc, char **argv)
{
  if (argc < 3)
    {
    cerr << "USAGE: " << argv[0] << "<output dir> <header files>" << endl;
    return 1;
    }

  std::string outputDir = argv[1];

  for (int i = 2; i < argc; i++)
    {
#ifdef DEBUG_PARSE
    cerr << "*** Parsing declarations from file " << argv[i] << endl;
#endif
    ifstream file(argv[i]);
    if (!file)
      {
      cerr << "Could not open " << argv[i] << endl;
      return 2;
      }

    while (!file.eof())
      {
      static char buf[4096];
      file.getline(buf, 4096);
      ParseLine(buf);
      }
    file.close();
    }

  ofstream hfile((outputDir + "/vtkgl.h").c_str());
  WriteHeader(hfile, argv[0], argv+1, argc-1);
  ofstream cxxfile((outputDir + "/vtkgl.cxx").c_str());
  WriteHeader(cxxfile, argv[0], argv+1, argc-1);

  WriteCode(hfile, cxxfile);

  hfile.close();
  cxxfile.close();

  return 0;
}
