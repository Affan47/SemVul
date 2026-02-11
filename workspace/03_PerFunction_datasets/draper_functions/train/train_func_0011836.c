op_error_string (const char *errmsg, int ntypes, bool match)
{
  const char *msg;

  const char *msgp = concat (match ? G_("ambiguous overload for ")
			           : G_("no match for "), errmsg, NULL);

  if (ntypes == 3)
    msg = concat (msgp, G_(" (operand types are %qT, %qT, and %qT)"), NULL);
  else if (ntypes == 2)
    msg = concat (msgp, G_(" (operand types are %qT and %qT)"), NULL);
  else
    msg = concat (msgp, G_(" (operand type is %qT)"), NULL);

  return msg;
}
