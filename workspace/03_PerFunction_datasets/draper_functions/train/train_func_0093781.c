EmitFnNameRecognizer(const std::vector<CodeGenIntrinsic> &Ints,
                     raw_ostream &OS) {

  std::map<char, std::vector<unsigned> > IntMapping;
  for (unsigned i = 0, e = Ints.size(); i != e; ++i)
    IntMapping[Ints[i].Name[5]].push_back(i);

  OS << "// Function name -> enum value recognizer code.\n";
  OS << "#ifdef GET_FUNCTION_RECOGNIZER\n";
  OS << "  StringRef NameR(Name+6, Len-6);   // Skip over 'llvm.'\n";
  OS << "  switch (Name[5]) {                  // Dispatch on first letter.\n";
  OS << "  default: break;\n";

  for (std::map<char, std::vector<unsigned> >::iterator I = IntMapping.begin(),
       E = IntMapping.end(); I != E; ++I) {
    OS << "  case '" << I->first << "':\n";
    std::vector<unsigned> &IntList = I->second;


    std::vector<StringMatcher::StringPair> MatchTable;

    for (unsigned i = 0, e = IntList.size(); i != e; ++i) {
      unsigned IntNo = IntList[i];
      std::string Result = "return " + TargetPrefix + "Intrinsic::" +
        Ints[IntNo].EnumName + ";";

      if (!Ints[IntNo].isOverloaded) {
        MatchTable.push_back(std::make_pair(Ints[IntNo].Name.substr(6),Result));
        continue;
      }


      std::string TheStr = Ints[IntNo].Name.substr(6);
      TheStr += '.';
      OS << "    if (NameR.startswith(\"" << TheStr << "\")) "
         << Result << '\n';
    }


    StringMatcher("NameR", MatchTable, OS).Emit(1);
    OS << "    break;  // end of '" << I->first << "' case.\n";
  }

  OS << "  }\n";
  OS << "#endif\n\n";
}
