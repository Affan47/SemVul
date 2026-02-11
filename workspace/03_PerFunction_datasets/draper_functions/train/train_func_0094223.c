PrintFailureInfo(const SourceMgr &SM, StringRef Buffer,
                               const StringMap<StringRef> &VariableTable) const{


  if (!VariableUses.empty()) {
    for (unsigned i = 0, e = VariableUses.size(); i != e; ++i) {
      StringRef Var = VariableUses[i].first;
      StringMap<StringRef>::const_iterator it = VariableTable.find(Var);
      SmallString<256> Msg;
      raw_svector_ostream OS(Msg);


      if (it == VariableTable.end()) {
        OS << "uses undefined variable \"";
        OS.write_escaped(Var) << "\"";;
      } else {
        OS << "with variable \"";
        OS.write_escaped(Var) << "\" equal to \"";
        OS.write_escaped(it->second) << "\"";
      }

      SM.PrintMessage(SMLoc::getFromPointer(Buffer.data()), SourceMgr::DK_Note,
                      OS.str());
    }
  }


  size_t NumLinesForward = 0;
  size_t Best = StringRef::npos;
  double BestQuality = 0;


  for (size_t i = 0, e = std::min(size_t(4096), Buffer.size()); i != e; ++i) {
    if (Buffer[i] == '\n')
      ++NumLinesForward;


    if (Buffer[i] == ' ' || Buffer[i] == '\t')
      continue;


    unsigned Distance = ComputeMatchDistance(Buffer.substr(i), VariableTable);
    double Quality = Distance + (NumLinesForward / 100.);

    if (Quality < BestQuality || Best == StringRef::npos) {
      Best = i;
      BestQuality = Quality;
    }
  }


  if (Best && Best != StringRef::npos && BestQuality < 50) {
      SM.PrintMessage(SMLoc::getFromPointer(Buffer.data() + Best),
                      SourceMgr::DK_Note, "possible intended match here");


  }
}
