maybeStatusKeyword(const Entity &entity)
{
  const InternalEntity *internal = entity.asInternalEntity();
  if (!internal)
    return 0;
  const StringC &text = internal->string();
  static const Syntax::ReservedName statusKeywords[] = {
    Syntax::rINCLUDE, Syntax::rIGNORE
    };
  for (size_t i = 0; i < SIZEOF(statusKeywords); i++) {
    const StringC &keyword = instanceSyntax().reservedName(statusKeywords[i]);
    size_t j = 0;
    while (j < text.size() && instanceSyntax().isS(text[j]))
      j++;
    size_t k = 0;
    while (j < text.size()
	   && k < keyword.size()
	   && ((*instanceSyntax().generalSubstTable())[text[j]]
	       == keyword[k]))
      j++, k++;
    if (k == keyword.size()) {
      while (j < text.size() && instanceSyntax().isS(text[j]))
	j++;
      if (j == text.size())
	return 1;
    }
  }
  return 0;
}
