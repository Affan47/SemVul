SwigType_typedef_class(const_String_or_char_ptr name) {
  String *cname;

  if (Getattr(current_typetab, name))
    return -1;
  cname = NewString(name);
  Setmeta(cname, "class", "1");
  Setattr(current_typetab, cname, cname);
  Delete(cname);
  flush_cache();
  return 0;
}
