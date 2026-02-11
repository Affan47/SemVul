run(raw_ostream &OS) {
  Target = CodeGenTarget(Records).getName();

  EmitSourceFileHeader("Subtarget Enumeration Source Fragment", OS);

  OS << "\n#ifdef GET_SUBTARGETINFO_ENUM\n";
  OS << "#undef GET_SUBTARGETINFO_ENUM\n";

  OS << "namespace llvm {\n";
  Enumeration(OS, "SubtargetFeature", true);
  OS << "} // End llvm namespace \n";
  OS << "#endif // GET_SUBTARGETINFO_ENUM\n\n";

  OS << "\n#ifdef GET_SUBTARGETINFO_MC_DESC\n";
  OS << "#undef GET_SUBTARGETINFO_MC_DESC\n";

  OS << "namespace llvm {\n";
#if 0
  OS << "namespace {\n";
#endif
  unsigned NumFeatures = FeatureKeyValues(OS);
  OS << "\n";
  unsigned NumProcs = CPUKeyValues(OS);
  OS << "\n";
  EmitData(OS);
  OS << "\n";
#if 0
  OS << "}\n";
#endif


  OS << "static inline void Init" << Target
     << "MCSubtargetInfo(MCSubtargetInfo *II, "
     << "StringRef TT, StringRef CPU, StringRef FS) {\n";
  OS << "  II->InitMCSubtargetInfo(TT, CPU, FS, ";
  if (NumFeatures)
    OS << Target << "FeatureKV, ";
  else
    OS << "0, ";
  if (NumProcs)
    OS << Target << "SubTypeKV, ";
  else
    OS << "0, ";
  if (HasItineraries) {
    OS << Target << "ProcItinKV, "
       << Target << "Stages, "
       << Target << "OperandCycles, "
       << Target << "ForwardingPathes, ";
  } else
    OS << "0, 0, 0, 0, ";
  OS << NumFeatures << ", " << NumProcs << ");\n}\n\n";

  OS << "} // End llvm namespace \n";

  OS << "#endif // GET_SUBTARGETINFO_MC_DESC\n\n";

  OS << "\n#ifdef GET_SUBTARGETINFO_TARGET_DESC\n";
  OS << "#undef GET_SUBTARGETINFO_TARGET_DESC\n";

  OS << "#include \"llvm/Support/Debug.h\"\n";
  OS << "#include \"llvm/Support/raw_ostream.h\"\n";
  ParseFeaturesFunction(OS, NumFeatures, NumProcs);

  OS << "#endif // GET_SUBTARGETINFO_TARGET_DESC\n\n";


  OS << "\n#ifdef GET_SUBTARGETINFO_HEADER\n";
  OS << "#undef GET_SUBTARGETINFO_HEADER\n";

  std::string ClassName = Target + "GenSubtargetInfo";
  OS << "namespace llvm {\n";
  OS << "struct " << ClassName << " : public TargetSubtargetInfo {\n"
     << "  explicit " << ClassName << "(StringRef TT, StringRef CPU, "
     << "StringRef FS);\n"
     << "};\n";
  OS << "} // End llvm namespace \n";

  OS << "#endif // GET_SUBTARGETINFO_HEADER\n\n";

  OS << "\n#ifdef GET_SUBTARGETINFO_CTOR\n";
  OS << "#undef GET_SUBTARGETINFO_CTOR\n";

  OS << "namespace llvm {\n";
  OS << "extern llvm::SubtargetFeatureKV " << Target << "FeatureKV[];\n";
  OS << "extern llvm::SubtargetFeatureKV " << Target << "SubTypeKV[];\n";
  if (HasItineraries) {
    OS << "extern llvm::SubtargetInfoKV " << Target << "ProcItinKV[];\n";
    OS << "extern llvm::InstrStage " << Target << "Stages[];\n";
    OS << "extern unsigned " << Target << "OperandCycles[];\n";
    OS << "extern unsigned " << Target << "ForwardingPathes[];\n";
  }

  OS << ClassName << "::" << ClassName << "(StringRef TT, StringRef CPU, "
     << "StringRef FS)\n"
     << "  : TargetSubtargetInfo() {\n"
     << "  InitMCSubtargetInfo(TT, CPU, FS, ";
  if (NumFeatures)
    OS << Target << "FeatureKV, ";
  else
    OS << "0, ";
  if (NumProcs)
    OS << Target << "SubTypeKV, ";
  else
    OS << "0, ";
  if (HasItineraries) {
    OS << Target << "ProcItinKV, "
       << Target << "Stages, "
       << Target << "OperandCycles, "
       << Target << "ForwardingPathes, ";
  } else
    OS << "0, 0, 0, 0, ";
  OS << NumFeatures << ", " << NumProcs << ");\n}\n\n";
  OS << "} // End llvm namespace \n";

  OS << "#endif // GET_SUBTARGETINFO_CTOR\n\n";
}
