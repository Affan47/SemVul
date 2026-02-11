is_table_sep(char *data, size_t pos){
  return data[pos]=='|' && (pos==0 || data[pos-1]!='\\');
}
