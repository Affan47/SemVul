getCharInfo(WideChar fromChar,
				 const PublicId *&id,
				 CharsetDeclRange::Type &type,
				 Number &n,
				 StringC &str,
				 Number &count) const
{
  for (size_t i = 0; i < sections_.size(); i++)
    if (sections_[i].getCharInfo(fromChar, id, type, n, str, count))
      return 1;
  return 0;
}
