print(InputLanguage lang, bool dagify) const {
  if(isNull()) {
    cout << "Null" << endl; return;
  }
  ExprStream os(getEM());
  os.lang(lang);
  os.dagFlag(dagify);
  os << *this << endl;
}
