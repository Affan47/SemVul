copy_value(Value *dst, Value *src)
{
  Value *dst_value;

  if (dst != NULL)
	dst_value = dst;
  else
	dst_value = ALLOC(Value);

  dst_value->token = src->token;
  dst_value->is_var_reference = src->is_var_reference;
  dst_value->is_alist_reference = src->is_alist_reference;
  dst_value->varname = (src->varname == NULL)
	? NULL : strdup(src->varname);
  dst_value->is_quoted = src->is_quoted;

  switch (src->token) {
  case T_REAL:
	dst_value->val.realval = src->val.realval;
	break;

  case T_INTEGER:
	dst_value->val.intval = src->val.intval;
	break;

  case T_LITERAL:
  case T_STRING:
	dst_value->val.strval = (src->val.strval == NULL)
	  ? NULL : strdup(src->val.strval);
	break;

  case T_VARIABLE:
	dst_value->val.strval = (src->val.strval == NULL)
	  ? NULL : strdup(src->val.strval);
	break;

  case T_BSTRING:
	dst_value->val.bval.data = memdupn(src->val.bval.data,
								   src->val.bval.len);
	dst_value->val.bval.len = src->val.bval.len;
	break;

  case T_LIST:
	dst_value->val.listval.list = dsvec_copy(NULL, src->val.listval.list);
	break;

  case T_ALIST:
	dst_value->val.alistval.kwv = kwv_copy(src->val.alistval.kwv);
	break;

  case T_DOTDOT:
	dst_value->val.dotdot.min = src->val.dotdot.min;
	dst_value->val.dotdot.max = src->val.dotdot.max;
	break;

  default:
	dst_value = NULL;
	break;
  }

  return(dst_value);
}
