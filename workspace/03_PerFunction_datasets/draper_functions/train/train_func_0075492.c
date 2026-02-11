lookupCreateId(const StringC &name)
{
  Id *id = idTable_.lookup(name);
  if (!id) {
    id = new Id(name);
    idTable_.insert(id);
  }
  return id;
}
