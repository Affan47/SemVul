GetMsg( short id ) const {
  if ( (id >= 0) && ((short)cat.size() > id) ) return cat[id].c_str();
  return 0;
}
