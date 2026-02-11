enumvalueDeclaration(Node *n) {
    String *name = Getattr(n, "name");
    String *qvalue = 0;

    if (name_qualifier) {
      qvalue = Copy(name_qualifier);
      Printv(qvalue, name, NIL);
    }

    if (const_enum && name && !Getattr(seen_enumvalues, name)) {
      Setattr(seen_enumvalues, name, "true");
      SetFlag(n, "feature:immutable");
      Setattr(n, "feature:enumvalue", "1");

      if (qvalue)
	Setattr(n, "qualified:value", qvalue);

      String *evname = SwigType_manglestr(qvalue);
      Insert(evname, 0, "SWIG_ENUM_");

      Setattr(n, "feature:enumvname", name);
      Setattr(n, "feature:symname", evname);
      Delete(evname);
      Printf(f_enumtypes_value, "| `%s\n", name);

      return Language::enumvalueDeclaration(n);
    } else
      return SWIG_OK;
  }
