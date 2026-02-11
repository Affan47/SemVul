ycompound(String name)
{
  HashMap<String, int> old_element_map(-1);
  old_element_map.swap(_element_map);
  HashMap<String, int> old_type_map(_element_type_map);
  int old_offset = _anonymous_offset;

  Compound *first = 0, *last = 0;
  int extension = -1;

  while (1) {
    Lexeme dots = lex();
    if (dots.is(lex3Dot)) {

      if (_element_type_map[name] < 0) {
	lerror("cannot extend unknown element class '%s'", name.c_str());
	ADD_ELEMENT_TYPE(name, error_element_factory, 0, true);
      }
      extension = _element_type_map[name];

      dots = lex();
      if (!first || !dots.is('}'))
	lerror("'...' should occur last, after one or more compounds");
      if (dots.is('}') && first)
	break;
    }
    unlex(dots);


    _element_map.clear();
    Compound *old_c = _c;
    Compound *ct = _c = new Compound(name, landmark(), &_c->_scope);
    get_element("input", TUNNEL_TYPE);
    get_element("output", TUNNEL_TYPE);
    _anonymous_offset = 2;

    ycompound_arguments(ct);
    while (ystatement(true))
      ;

    _anonymous_offset = old_offset;
    _element_type_map = old_type_map;
    _c = old_c;

    ct->finish(this, _errh);

    if (last) {
      int t = ADD_ELEMENT_TYPE(name, compound_element_factory, (uintptr_t) ct, true);
      last->set_overload_type(t);
    } else
      first = ct;
    last = ct;


    const Lexeme &t = lex();
    if (!t.is(lex2Bar))
      break;
  }


  old_element_map.swap(_element_map);


  if (extension)
    last->set_overload_type(extension);
  return ADD_ELEMENT_TYPE(name, compound_element_factory, (uintptr_t) first, true);
}
