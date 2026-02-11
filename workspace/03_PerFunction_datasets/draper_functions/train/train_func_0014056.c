make(ELObj *obj, const Location &loc,
			    Interpreter &interp) const
{
  const Char *s;
  size_t n;
  if (obj->stringData(s, n))
    return new ExtensionStringInheritedC(identifier(), index(), setter_, s, n);
  invalidValue(loc, interp);
  return ConstPtr<InheritedC>();
}
