addSymbol(const string &name, SymbolType type, const string &tex_name, const string &long_name) throw (AlreadyDeclaredException, FrozenException)
{
  if (frozen)
    throw FrozenException();

  if (exists(name))
    {
      if (type_table[getID(name)] == type)
        throw AlreadyDeclaredException(name, true);
      else
        throw AlreadyDeclaredException(name, false);
    }

  int id = size++;

  symbol_table[name] = id;
  type_table.push_back(type);
  name_table.push_back(name);
  tex_name_table.push_back(tex_name);
  long_name_table.push_back(long_name);

  return id;
}
