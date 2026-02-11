LookupNearestOption(StringRef Arg,
                                   const StringMap<Option*> &OptionsMap,
                                   std::string &NearestString) {

  if (Arg.empty()) return 0;


  std::pair<StringRef, StringRef> SplitArg = Arg.split('=');
  StringRef &LHS = SplitArg.first;
  StringRef &RHS = SplitArg.second;


  Option *Best = 0;
  unsigned BestDistance = 0;
  for (StringMap<Option*>::const_iterator it = OptionsMap.begin(),
         ie = OptionsMap.end(); it != ie; ++it) {
    Option *O = it->second;
    SmallVector<const char*, 16> OptionNames;
    O->getExtraOptionNames(OptionNames);
    if (O->ArgStr[0])
      OptionNames.push_back(O->ArgStr);

    bool PermitValue = O->getValueExpectedFlag() != cl::ValueDisallowed;
    StringRef Flag = PermitValue ? LHS : Arg;
    for (size_t i = 0, e = OptionNames.size(); i != e; ++i) {
      StringRef Name = OptionNames[i];
      unsigned Distance = StringRef(Name).edit_distance(
        Flag, true, BestDistance);
      if (!Best || Distance < BestDistance) {
        Best = O;
        BestDistance = Distance;
	if (RHS.empty() || !PermitValue)
	  NearestString = OptionNames[i];
	else
	  NearestString = std::string(OptionNames[i]) + "=" + RHS.str();
      }
    }
  }

  return Best;
}
