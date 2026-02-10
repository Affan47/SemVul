PropertyOfSameObject(Expression* e1, Expression* e2) {
    Property* p1 = e1->AsProperty();
    Property* p2 = e2->AsProperty();
    if ((p1 == NULL) || (p2 == NULL)) return false;
    return SameObject(p1->obj(), p2->obj());
  }
