writeLiteralExpr(const string& src) {
  stringstream s;
  s << "push " << src;
  writeTEXT(s.str());
}
