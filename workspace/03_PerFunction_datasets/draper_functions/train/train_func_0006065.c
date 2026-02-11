new_rule_double(char *property, Ordertype order, double value)
{
  Term t;
  char *s = NULL;
  switch(order) {
  case LESS_THAN: s = "<";  break;
  case LESS_THAN_OR_SAME_AS: s = "<=";  break;
  case SAME_AS: s = "=";  break;
  case GREATER_THAN_OR_SAME_AS: s = ">=";  break;
  case GREATER_THAN: s = ">";  break;
  default: fatal_error("new_rule_double, bad relation");
  }
  t = get_rigid_term(s, 2);
  ARG(t,0) = get_rigid_term(property, 0);
  ARG(t,1) = double_to_term(value);
  return t;
}
