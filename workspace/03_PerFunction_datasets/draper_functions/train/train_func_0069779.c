_kt_lookup_keybinding(KeyTab *kt, const char *binary_keyseq,
				 int nc, KeySym **matches, int *nmatch)
{
  KtKeyMatch status;
  int first,last;


  if(!kt || !binary_keyseq || !matches || !nmatch || nc < 0) {
    errno = EINVAL;
    if(kt)
      _err_record_msg(kt->err, "NULL argument(s)", END_ERR_MSG);
    return KT_BAD_MATCH;
  };


  status = _kt_locate_keybinding(kt, binary_keyseq, nc, &first, &last);


  switch(status) {
  case KT_EXACT_MATCH:
  case KT_AMBIG_MATCH:
    *matches = kt->table + first;
    *nmatch = last - first + 1;
    break;
  default:
    *matches = NULL;
    *nmatch = 0;
    break;
  };
  return status;
}
