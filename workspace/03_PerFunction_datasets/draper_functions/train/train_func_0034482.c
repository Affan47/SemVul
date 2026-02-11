check_lang(ParmString l) {
    if (l != lang_->name())
      return make_err(mismatched_language, lang_->name(), l);
    return no_err;
  }
