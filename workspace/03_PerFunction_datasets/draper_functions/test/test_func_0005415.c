nextLabel(const string& labelName) {
  string::const_iterator x;
  string::const_iterator xend;
  const string::const_iterator lend = labelName.end();
  while (true) {

    ++*this;
    if (isSection()) return 0;


    x = p->text.begin();
    xend = p->text.end();

    if (advanceWhitespace(x, xend)) continue;


    string::const_iterator l = labelName.begin();
    while (x != xend && l != lend && *x == *l) { ++x; ++l; }
    if (l == lend
        && !advanceWhitespace(x, xend)
        && *x == '=')
      return x - p->text.begin() + 1;
  }
}
