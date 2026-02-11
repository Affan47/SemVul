stack_op(Expression* E)const
{
  assert(E);

  bool been_here = false;
  std::string tmp;
  for (;;) {
    const Token* t = E->back();
    E->pop_back();
    if (dynamic_cast<const Token_STOP*>(t)) {

      break;
    }else{
      if (been_here) {
	tmp = ", " + tmp;
      }else{
	been_here = true;
      }
      tmp = t->name() + tmp;
    }
    delete t;
  }
  E->push_back(new Token_PARLIST(tmp));
}
