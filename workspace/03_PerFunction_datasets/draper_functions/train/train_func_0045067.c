classDeclaration(Node *n) {
    if (!Getattr(n, "feature:onlychildren")) {
      String *name = Getattr(n, "name");
      String *symname = Getattr(n, "sym:name");
      String *tdname = Getattr(n, "tdname");

      name = tdname ? tdname : name;
      String *namestr = SwigType_namestr(name);
      klass = RCLASS(classes, Char(namestr));
      if (!klass) {
	klass = new RClass();
	String *valid_name = NewString(symname ? symname : namestr);
	validate_const_name(Char(valid_name), "class");
	klass->set_name(namestr, symname, valid_name);
	SET_RCLASS(classes, Char(namestr), klass);
	Delete(valid_name);
      }
      Delete(namestr);
    }
    return Language::classDeclaration(n);
  }
