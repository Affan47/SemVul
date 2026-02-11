arg_eval_bool (CSPARSE *parse, CSARG *arg)
{
  long int v = 0;
  char *s, *r;

  switch ((arg->op_type & CS_TYPES))
  {
    case CS_TYPE_STRING:
    case CS_TYPE_VAR:
      if (arg->op_type == CS_TYPE_VAR)
	s = var_lookup(parse, arg->s);
      else
	s = arg->s;
      if (!s || *s == '\0') return 0;
      v = strtol(s, &r, 0);
      if (*r == '\0')
	return v;


      return 1;
    case CS_TYPE_NUM:
      return arg->n;
    case CS_TYPE_VAR_NUM:
      return var_int_lookup (parse, arg->s);
      break;
    default:
      ne_warn ("Unsupported type %s in arg_eval_bool", expand_token_type(arg->op_type, 1));
      v = 0;
      break;
  }
  return v;
}
