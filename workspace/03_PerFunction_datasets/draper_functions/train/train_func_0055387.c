FinishFunction() {

  if (!P.ForwardRefBlockAddresses.empty()) {
    ValID FunctionID;
    if (!F.getName().empty()) {
      FunctionID.Kind = ValID::t_GlobalName;
      FunctionID.StrVal = F.getName();
    } else {
      FunctionID.Kind = ValID::t_GlobalID;
      FunctionID.UIntVal = FunctionNumber;
    }

    std::map<ValID, std::vector<std::pair<ValID, GlobalValue*> > >::iterator
      FRBAI = P.ForwardRefBlockAddresses.find(FunctionID);
    if (FRBAI != P.ForwardRefBlockAddresses.end()) {

      if (P.ResolveForwardRefBlockAddresses(&F, FRBAI->second, this))
        return true;

      P.ForwardRefBlockAddresses.erase(FRBAI);
    }
  }

  if (!ForwardRefVals.empty())
    return P.Error(ForwardRefVals.begin()->second.second,
                   "use of undefined value '%" + ForwardRefVals.begin()->first +
                   "'");
  if (!ForwardRefValIDs.empty())
    return P.Error(ForwardRefValIDs.begin()->second.second,
                   "use of undefined value '%" +
                   Twine(ForwardRefValIDs.begin()->first) + "'");
  return false;
}
