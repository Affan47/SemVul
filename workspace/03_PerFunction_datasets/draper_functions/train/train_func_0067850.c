free_token (token_ty *tp)
{
  if (tp->type == token_type_string || tp->type == token_type_symbol)
    free (tp->string);
  if (tp->type == token_type_string)
    drop_reference (tp->comment);
}
