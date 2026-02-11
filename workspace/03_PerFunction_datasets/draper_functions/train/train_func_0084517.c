operator==(const ExportEntry &Other) const {

  if (Done || Other.Done)
    return (Done == Other.Done);

  if (Stack.size() != Other.Stack.size())
    return false;

  if (!CumulativeString.equals(Other.CumulativeString))
    return false;

  for (unsigned i=0; i < Stack.size(); ++i) {
    if (Stack[i].Start != Other.Stack[i].Start)
      return false;
  }
  return true;
}
