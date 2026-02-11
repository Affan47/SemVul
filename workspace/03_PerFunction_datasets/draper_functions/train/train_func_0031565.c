EmitTypeGenerate(raw_ostream &OS,
                             const std::vector<Record*> &ArgTypes,
                             unsigned &ArgNo) {
  if (ArgTypes.empty())
    return EmitTypeForValueType(OS, MVT::isVoid);

  if (ArgTypes.size() == 1)
    return EmitTypeGenerate(OS, ArgTypes.front(), ArgNo);

  OS << "StructType::get(";

  for (std::vector<Record*>::const_iterator
         I = ArgTypes.begin(), E = ArgTypes.end(); I != E; ++I) {
    EmitTypeGenerate(OS, *I, ArgNo);
    OS << ", ";
  }

  OS << " NULL)";
}
