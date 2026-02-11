ParseGlobalValue(Type *Ty, Constant *&C) {
  C = 0;
  ValID ID;
  Value *V = NULL;
  bool Parsed = ParseValID(ID) ||
                ConvertValIDToValue(Ty, ID, V, NULL);
  if (V && !(C = dyn_cast<Constant>(V)))
    return Error(ID.Loc, "global values must be constants");
  return Parsed;
}
