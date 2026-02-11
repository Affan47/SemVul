help()
{
  cout << "Open Babel converts chemical structures from one file format to another"<< endl << endl;
  cout << "Usage: " << endl;
  cout << program_name << "[-i<input-type>] <infilename> [-o<output-type>] -O<outfilename> [Options]" << endl;
  cout << "The extension of a file decides the format, unless it is overridden" <<endl;
  cout << " by -i or -o options, e.g. -icml, or -o smi" << endl;
  cout << "See below for available format-types, which are the same as the " << endl;
  cout << "file extensions and are case independent." << endl;
  cout << "If no input or output file is given stdin or stdout are used instead." << endl << endl;
  cout << "More than one input file can be specified and their names can contain" <<endl;
  cout << "wildcard chars (* and ?). The format of each file can be different unless" <<endl;
  cout << "the -i option has been used, when they are all the same." <<endl;
  cout << "By default, the molecules are aggregated in the output file," << endl;
  cout << " but see -m option, Splitting, below.\n" << endl;

  cout << "Options, other than -i -o -O -m, must come after the input files.\n" <<endl;
  cout << OBConversion::Description();
  cout << "-H Outputs this help text" << endl;
  cout << "-Hxxx (xxx is file format ID e.g. -Hcml) gives format info" <<endl;
  cout << "-Hall Outputs details of all formats" <<endl;
  cout << "-V Outputs version number" <<endl;
  cout << "-L <category> Lists plugin classes of this category, e.g. <formats>" << endl;
  cout << "   Use just -L for a list of plugin categories." << endl;
  cout << "   Use -L <ID> e.g. -L sdf for details of a format or other plugin." << endl;
  cout << "-m Produces multiple output files, to allow:" <<endl;
  cout << "    Splitting: e.g.        " << program_name << " infile.mol -O new.smi -m" <<endl;
  cout << "      puts each molecule into new1.smi new2.smi etc" <<endl;
  cout << "    Batch conversion: e.g. " << program_name << " *.mol -osmi -m" <<endl;
  cout << "      converts each input file to a .smi file" << endl;
#ifdef _WIN32
  cout << "   In Windows these can also be done using the forms" <<endl;
  cout << "     " << program_name << " infile.mol -O new*.smi and " << program_name << " *.mol -O *.smi respectively.\n" <<endl;
#endif

  OBFormat* pDefault = OBConversion::GetDefaultFormat();
  if(pDefault)
    cout << pDefault->TargetClassDescription();

  OBFormat* pAPI= OBConversion::FindFormat("obapi");
  if(pAPI)
    cout << pAPI->Description();

  cout << "To see a list of recognized file formats use\n  babel -L formats [read] [write]\n"
       << "To see details and specific options for a particular format, e.g CML, use\n  babel -L cml\n"
       << endl;


}
