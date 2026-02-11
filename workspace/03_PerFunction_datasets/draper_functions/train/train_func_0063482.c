destructorDeclaration(Node *n) {
    (void) n;
    if (!inclass)
      return SWIG_OK;
    if (!extendmode) {
      Setattr(inclass, "allocate:has_destructor", "1");
      if (cplus_mode == PUBLIC) {
	Setattr(inclass, "allocate:default_destructor", "1");
      } else if (cplus_mode == PROTECTED) {
	Setattr(inclass, "allocate:default_base_destructor", "1");
      }
    }
    return SWIG_OK;
  }
