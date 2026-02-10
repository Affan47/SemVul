addGlobalVariable(DIGlobalVariable DIG) {
  if (!DIDescriptor(DIG).isGlobalVariable())
    return false;

  if (!NodesSeen.insert(DIG))
    return false;

  GVs.push_back(DIG);
  return true;
}
