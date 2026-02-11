main(int argc, char **argv) {

  sys::PrintStackTraceOnErrorSignal();
  PrettyStackTraceProgram X(argc, argv);

  llvm_shutdown_obj Y;
  cl::ParseCommandLineOptions(argc, argv, "llvm object size dumper\n");

  ToolName = argv[0];
  if (OutputFormatShort.getNumOccurrences())
    OutputFormat = static_cast<OutputFormatTy>(OutputFormatShort);
  if (RadixShort.getNumOccurrences())
    Radix = RadixShort;

  for (unsigned i = 0; i < ArchFlags.size(); ++i) {
    if (ArchFlags[i] == "all") {
      ArchAll = true;
    } else {
      if (!MachOObjectFile::isValidArch(ArchFlags[i])) {
        outs() << ToolName << ": for the -arch option: Unknown architecture "
               << "named '" << ArchFlags[i] << "'";
        return 1;
      }
    }
  }

  if (InputFilenames.size() == 0)
    InputFilenames.push_back("a.out");

  moreThanOneFile = InputFilenames.size() > 1;
  std::for_each(InputFilenames.begin(), InputFilenames.end(),
                PrintFileSectionSizes);

  return 0;
}
