func_digest(Lex_state *e, int nargs, Arglist *arglist, Expr_result *result)
{
  unsigned int digest_len, msg_len;
  char *digest_name, *msg_str;
  unsigned char *digest;
  Arglist *x;

  x = arglist;
  if (x->result->value.token == T_STRING) {
	msg_str = x->result->value.val.strval;
	x = x->next;
	if ((msg_len = x->result->value.val.intval) == 0)
	  msg_len = strlen(msg_str);
  }
  else if (x->result->value.token == T_BSTRING) {
	msg_str = x->result->value.val.bval.data;
	x = x->next;
	if ((msg_len = x->result->value.val.intval) == 0)
	  msg_len = x->result->value.val.bval.len;
  }
  else {
	seterr_e(e, result, "digest function failed: invalid argument");
	return(-1);
  }
  x = x->next;

  if (x != NULL) {
	if (x->next != NULL) {
	  seterr_e(e, result, "digest function failed: too many arguments");
	  return(-1);
	}

	if (!str_or_lit(x->result->value.token)) {
	  seterr_e(e, result, "digest function failed: unrecognized digest name");
	  return(-1);
	}
	digest_name = strtoupper(x->result->value.val.strval);
  }
  else
	digest_name = "SHA1";

  digest = crypto_digest(digest_name, msg_str, msg_len, NULL, &digest_len);
  if (digest == NULL) {
	seterr_e(e, result, "digest function failed");
	return(-1);
  }

  result->value.token = T_BSTRING;
  result->value.val.bval.data = (void *) digest;
  result->value.val.bval.len = (size_t) digest_len;

  return(0);
}
