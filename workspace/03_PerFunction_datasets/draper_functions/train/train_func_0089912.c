instantiate_inheritable_attributes(Attribute a, Context subst)
{
  Attribute b;
  for (b = a; b; b = b->next) {
    if (attribute_type(b) == TERM_ATTRIBUTE && inheritable(b)) {
      Term t = apply(b->u.t, subst);
      zap_term(b->u.t);
      b->u.t = t;
    }
  }
}
