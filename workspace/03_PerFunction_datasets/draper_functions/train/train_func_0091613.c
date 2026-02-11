ToString() {
  if (this == NULL) {


    return "";
  }

  if (is_exact_) {
    int n = 0;
    string s;
    for (set<string>::iterator i = exact_.begin(); i != exact_.end(); ++i) {
      if (n++ > 0)
        s += ",";
      s += *i;
    }
    return s;
  }

  if (match_)
    return match_->DebugString();

  return "";
}
