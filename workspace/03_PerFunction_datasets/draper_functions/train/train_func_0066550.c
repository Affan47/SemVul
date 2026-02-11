get(Metadata &MD) {
  if (auto *N = dyn_cast<MDNode>(&MD))
    return N->Context.getReplaceableUses();
  return dyn_cast<ValueAsMetadata>(&MD);
}
