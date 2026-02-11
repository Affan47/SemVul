get(int id) {
  int i;


  for(i=ids.size()-1;i>=0;i--)
    if (ids[i] == id) return( text[i] );
  return 0;
}
