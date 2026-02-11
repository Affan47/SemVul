getCharInfo(WideChar fromChar,
					const PublicId *&id,
					CharsetDeclRange::Type &type,
					Number &n,
					StringC &str,
					Number &count) const
{
  for (size_t i = 0; i < ranges_.size(); i++)
    if (ranges_[i].getCharInfo(fromChar, type, n, str, count)) {
      id = &baseset_;
      return 1;
    }
  return 0;
}
