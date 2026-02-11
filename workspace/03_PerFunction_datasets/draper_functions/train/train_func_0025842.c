main(int argc, char **argv) {

  sys::PrintStackTraceOnErrorSignal();
  PrettyStackTraceProgram X(argc, argv);

  llvm_shutdown_obj Y;
  cl::ParseCommandLineOptions(argc, argv, "llvm object size dumper\n");

  ToolName = argv[0];
  if (OutputFormatShort.getNumOccurrences())
    OutputFormat = OutputFormatShort;
  if (RadixShort.getNumOccurrences())
    Radix = RadixShort;

  if (InputFilenames.size() == 0)
    InputFilenames.push_back("a.out");

  if (OutputFormat == berkeley)
    outs() << "   text    data     bss     "
           << (Radix == octal ? "oct" : "dec")
           << "     hex filename\n";

  std::for_each(InputFilenames.begin(), InputFilenames.end(),
                PrintFileSectionSizes);

  return 0;
}
