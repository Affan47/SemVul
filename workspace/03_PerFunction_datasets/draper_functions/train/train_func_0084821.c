stack_op(Expression* E)const
{
  assert(E);

  Token* t1 = E->back();
  E->pop_back();
  if (dynamic_cast<Token_CONSTANT*>(t1)) {
    Token* t = op(t1);
    assert(t);
    if (t->data()) {
      E->push_back(t);
      delete t1;
    }else{untested();
      E->push_back(t1);
      E->push_back(clone());
      delete t;
    }
  }else{untested();
    E->push_back(t1);
    E->push_back(clone());
  }
}
