d_unqualified_name (struct d_info *di)
{
  char peek;

  peek = d_peek_char (di);
  if (IS_DIGIT (peek))
    return d_source_name (di);
  else if (IS_LOWER (peek))
    {
      struct demangle_component *ret;

      ret = d_operator_name (di);
      if (ret != NULL && ret->type == DEMANGLE_COMPONENT_OPERATOR)
	di->expansion += sizeof "operator" + ret->u.s_operator.op->len - 2;
      return ret;
    }
  else if (peek == 'C' || peek == 'D')
    return d_ctor_dtor_name (di);
  else if (peek == 'L')
    {
      struct demangle_component * ret;

      d_advance (di, 1);

      ret = d_source_name (di);
      if (ret == NULL)
	return NULL;
      if (! d_discriminator (di))
	return NULL;
      return ret;
    }
  else if (peek == 'U')
    {
      switch (d_peek_next_char (di))
	{
	case 'l':
	  return d_lambda (di);
	case 't':
	  return d_unnamed_type (di);
	default:
	  return NULL;
	}
    }
  else
    return NULL;
}
