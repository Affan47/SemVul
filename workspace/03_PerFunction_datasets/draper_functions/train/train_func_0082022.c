Swig_name_get(const_String_or_char_ptr vname) {
  String *r;
  String *f;

#ifdef SWIG_DEBUG
  Printf(stdout, "Swig_name_get:  '%s'\n", vname);
#endif

  r = NewStringEmpty();
  if (!naming_hash)
    naming_hash = NewHash();
  f = Getattr(naming_hash, "get");
  if (!f) {
    Append(r, "%v_get");
  } else {
    Append(r, f);
  }
  Replace(r, "%v", vname, DOH_REPLACE_ANY);

  return r;
}
