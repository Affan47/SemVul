staticmemberfunctionHandler(Node *n) {
    String *symname = Getattr(n, "sym:name");
    Language::staticmemberfunctionHandler(n);

    if (Getattr(n, "sym:nextSibling")) {
      return SWIG_OK;
    }

    if (shadow) {
      if (!classic && !Getattr(n, "feature:python:callback") && have_addtofunc(n)) {
	int kw = (check_kwargs(n) && !Getattr(n, "sym:overloaded")) ? 1 : 0;
        String *parms = make_pyParmList(n, false, false, kw);
        String *callParms = make_pyParmList(n, false, true, kw);
	Printv(f_shadow, tab4, "def ", symname, "(", parms, ")", returnTypeAnnotation(n), ":\n", NIL);
	if (have_docstring(n))
	  Printv(f_shadow, tab8, docstring(n, AUTODOC_STATICFUNC, tab8), "\n", NIL);
	if (have_pythonprepend(n))
	  Printv(f_shadow, pythoncode(pythonprepend(n), tab8), "\n", NIL);
	if (have_pythonappend(n)) {
	  Printv(f_shadow, tab8, "val = ", funcCall(Swig_name_member(class_name, symname), callParms), "\n", NIL);
	  Printv(f_shadow, pythoncode(pythonappend(n), tab8), "\n", NIL);
	  Printv(f_shadow, tab8, "return val\n\n", NIL);
	} else {
	  Printv(f_shadow, tab8, "return ", funcCall(Swig_name_member(class_name, symname), callParms), "\n\n", NIL);
	}
	Printv(f_shadow, tab4, modern ? "" : "if _newclass:", symname, " = staticmethod(", symname, ")\n", NIL);

	if (!modern) {
	  Printv(f_shadow, tab4, "__swig_getmethods__[\"", symname, "\"] = lambda x: ", symname, "\n", NIL);
	}

      } else {
	if (!modern) {
	  Printv(f_shadow, tab4, "__swig_getmethods__[\"", symname, "\"] = lambda x: ", module, ".", Swig_name_member(class_name, symname), "\n", NIL);
	}
	if (!classic) {
	  Printv(f_shadow, tab4, modern ? "" : "if _newclass:", symname, " = staticmethod(", module, ".", Swig_name_member(class_name, symname), ")\n", NIL);
	}
      }
    }
    return SWIG_OK;
  }
