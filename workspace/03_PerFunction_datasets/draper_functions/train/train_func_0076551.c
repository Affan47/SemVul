find(string s)
{


  const char scopeOperator = '.';
  size_t scopeOperatorPosition = s.find_first_of(scopeOperator);
  if (scopeOperatorPosition != string::npos) {
    searchTable = &globalSymbols;
    if (scopeOperatorPosition == 0) {
      searchTable = currentSymbolTable;
      scopeOperatorPosition++;
    }
    else {

      string moduleName = s.substr(0, scopeOperatorPosition);
      MSymbolTable_t::iterator mti = MSymbolTables.find(moduleName);
      if (mti != MSymbolTables.end()) {
        searchTable = mti->second;
        scopeOperatorPosition++;
      }
    }
    SymbolTable_t::iterator sti = searchTable->find(s.substr(scopeOperatorPosition,string::npos));
    if (sti != searchTable->end())
      return sti->second;
  }

  pFound = 0;
  searchString = s;
  MSymbolTable_t::iterator mti = find_if (MSymbolTables.begin(), MSymbolTables.end(), tpred);
  if (mti != MSymbolTables.end())
    searchTable = mti->second;

  return pFound;
}
