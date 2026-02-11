add_positive_restriction_element(expr_t value, string *variable, string *lag)
{

  if (!svar_left_handside)
    value = add_uminus(value);

  add_restriction_element(value, variable, lag);
}
