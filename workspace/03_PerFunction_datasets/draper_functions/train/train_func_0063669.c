operator<<( ostream& os, const parseData& pd ){
  os << "pd words " << pd.words << endl;
  os << "pd heads " << pd.heads << endl;
  os << "pd mods " << pd.mods << endl;
  os << "pd mwus ";
  for ( size_t i=0; i < pd.mwus.size(); ++i ){
    for ( size_t j=0; j < pd.mwus[i].size(); ++j )
      os << pd.mwus[i][j]->id();
    os << endl;
  }
  return os;
}
