phase8a_get (token_ty *tp)
{
  phase6_get (tp);
  if (tp->type == token_type_name && is_inttypes_macro (tp->string))
    {

      char *new_string = xasprintf ("<%s>", tp->string);
      free (tp->string);
      tp->string = new_string;
      tp->comment = add_reference (savable_comment);
      tp->type = token_type_string_literal;
    }
}
