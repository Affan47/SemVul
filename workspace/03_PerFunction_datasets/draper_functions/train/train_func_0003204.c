LookupUnicodeGroup(const StringPiece& name) {

  if (name == StringPiece("Any"))
    return &anygroup;
  return LookupGroup(name, unicode_groups, num_unicode_groups);
}
