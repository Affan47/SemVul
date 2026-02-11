add_repl(ParmString mis, ParmString cor)
  {
    if (!invisible_soundslike) {
      VARARRAY(char, sl, mis.size() + 1);
      lang()->LangImpl::to_soundslike(sl, mis.str(), mis.size());
      return add_repl(mis, cor, sl);
    } else {
      return add_repl(mis, cor, "");
    }
  }
