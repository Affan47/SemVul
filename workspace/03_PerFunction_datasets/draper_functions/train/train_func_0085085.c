find_word(const char* word,
                         unsigned& line, string::size_type& pos) {
  for (unsigned i=line; i<lines.size(); ++i) {
    string::size_type s = (pos==0) ? lines[i].find(sentinel) + slen : pos;
    string::size_type w = lines[i].find(word, s);
    string::size_type c = lines[i].find('!', s);

    if ( w != string::npos &&
         (c == string::npos || (c != string::npos && w < c))
       ) {
      line = i;
      pos  = w;
      return true;
    }
    pos = 0;
  }
  return false;
}
