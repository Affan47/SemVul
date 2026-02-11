generalName(const StringC &name,
					          StringC &buf)
{
  if (options_.lower && namecaseGeneral_) {
    for (size_t i = 0; i < name.size(); i++) {
      Char c = lowerSubst_[name[i]];
      if (c != name[i]) {
	buf = name;
	buf[i] = c;
	for (i++; i < name.size(); i++)
	  lowerSubst_.subst(buf[i]);
	return buf;
      }
    }
  }
  return name;
}
