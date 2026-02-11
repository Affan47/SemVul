SwigType_typedef_using(const_String_or_char_ptr name) {
  String *base;
  String *td;
  String *prefix;
  Typetab *s;
  Typetab *tt = 0;

  String *defined_name = 0;


  if (!Swig_scopename_check(name))
    return -1;
  base = Swig_scopename_last(name);


  if (Getattr(current_typetab, base)) {
    Delete(base);
    return -1;
  }


  Setattr(current_typetab, base, name);


  td = SwigType_typedef_resolve(name);

  if (resolved_scope) {
    defined_name = Getattr(resolved_scope, "qname");
    if (defined_name) {
      defined_name = Copy(defined_name);
      Append(defined_name, "::");
      Append(defined_name, base);

      tt = SwigType_find_scope(current_scope, defined_name);
    }
  }
  if (td)
    Delete(td);


  {
    prefix = Swig_scopename_prefix(name);
    s = SwigType_find_scope(current_scope, prefix);
    if (s) {
      Hash *ttab = Getattr(s, "typetab");
      if (!Getattr(ttab, base) && defined_name) {
	Setattr(ttab, base, defined_name);
      }
    }
  }

  if (tt) {

    SwigType_new_scope(base);
    SwigType_inherit_scope(tt);
    SwigType_pop_scope();
  }

  if (defined_name)
    Delete(defined_name);
  Delete(prefix);
  Delete(base);
  return 0;
}
