hasNaughty() {
  vector<Page *>::iterator i;
  for(i=pages.begin();i!=pages.end();i++)
    if ( (*i)->naughty )
      return true;
  return false;
}
