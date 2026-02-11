ann2svalsel(AST::Node* ann, std::string r0, std::string r1,
                           Rnd rnd) {
    (void) rnd;
    if (AST::Atom* s = dynamic_cast<AST::Atom*>(ann)) {
      if (s->id == "indomain_min") {
        r0 = "in"; r1 = "not in";
        return SET_VAL_MIN_INC();
      }
      if (s->id == "indomain_max") {
        r0 = "in"; r1 = "not in";
        return SET_VAL_MAX_INC();
      }
      if (s->id == "outdomain_min") {
        r1 = "in"; r0 = "not in";
        return SET_VAL_MIN_EXC();
      }
      if (s->id == "outdomain_max") {
        r1 = "in"; r0 = "not in";
        return SET_VAL_MAX_EXC();
      }
    }
    std::cerr << "Warning, ignored search annotation: ";
    ann->print(std::cerr);
    std::cerr << std::endl;
    r0 = "in"; r1 = "not in";
    return SET_VAL_MIN_INC();
  }
