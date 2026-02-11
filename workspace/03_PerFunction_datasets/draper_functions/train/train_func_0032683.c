add_change(const string& lhs, const string& cond, int bytes, const string& value) {
  changes_.insert(make_pair(make_pair(lhs, cond), make_pair(bytes, value)));
}
