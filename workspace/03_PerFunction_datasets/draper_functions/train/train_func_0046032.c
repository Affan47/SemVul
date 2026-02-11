enumValue(Node *n) {
    String *symname = Getattr(n, "sym:name");


    String *value = Getattr(n, "feature:cs:constvalue");

    if (!value) {

      int const_feature_flag = GetFlag(n, "feature:cs:const");

      if (const_feature_flag) {

	value = Getattr(n, "enumvalue") ? Copy(Getattr(n, "enumvalue")) : Copy(Getattr(n, "enumvalueex"));
      } else {

	if (!getCurrentClass() || !cparse_cplusplus || !proxy_flag) {

	  Setattr(n, "name", Getattr(n, "value"));
	  constantWrapper(n);
	  value = NewStringf("%s.%s()", imclass_name, Swig_name_get(symname));
	} else {
	  memberconstantHandler(n);
	  value = NewStringf("%s.%s()", imclass_name, Swig_name_get(Swig_name_member(proxy_class_name, symname)));
	}
      }
    }
    return value;
  }
