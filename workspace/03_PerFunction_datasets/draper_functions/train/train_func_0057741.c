set(std::string name, std::string s) {
    t_atom a;
    SETSYMBOL(&a, gensym(s.c_str()));
    set(name, &a);
  }
