main(int argc, char **argv) {
  ProgramName = argv[0];
  llvm_shutdown_obj Y;

  cl::ParseCommandLineOptions(argc, argv, "llvm Mach-O dumping tool\n");


  std::string ErrorStr;
  OwningPtr<MemoryBuffer> InputBuffer;
  if (error_code ec = MemoryBuffer::getFileOrSTDIN(InputFile, InputBuffer))
    return Error("unable to read input: '" + ec.message() + "'");


  OwningPtr<MachOObject> InputObject(
    MachOObject::LoadFromBuffer(InputBuffer.take(), &ErrorStr));
  if (!InputObject)
    return Error("unable to load object: '" + ErrorStr + "'");


  InputObject->printHeader(outs());


  int Res = 0;
  outs() << "('load_commands', [\n";
  for (unsigned i = 0; i != InputObject->getHeader().NumLoadCommands; ++i)
    if ((Res = DumpLoadCommand(*InputObject, i)))
      break;
  outs() << "])\n";

  return Res;
}
