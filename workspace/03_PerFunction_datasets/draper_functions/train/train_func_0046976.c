table_cell_length(const char *z){
  Markup markup;
  int i = 0;

  while( z[i] && z[i]!='|' && z[i]!='\n' ){
    if( z[i]=='{' && is_markup(&z[i],&markup) ){
      i += markup.lenTotal;
    }else{
      i++;
    }
  }
  return (z[i]=='|') ? i : 0;
}
