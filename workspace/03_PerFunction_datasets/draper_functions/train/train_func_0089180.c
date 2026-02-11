next(STR *s)
{
  int ch, rc;

  switch (s->state) {
  case EOS:
	return(0);
  case INFINITE:
	return(1);
  case NORMAL:
	switch (ch = *s->str) {
	case '\0':
	  s->state = EOS;
	  return(0);
	case '\\':
	  s->lastch = backslash(s);
	  break;
	case '[':
	  if ((rc = bracket(s)) == -1)
		return(-1);
	  else if (rc)
		return (next(s));

	default:
	  ++s->str;
	  s->lastch = ch;
	  break;
	}


	if (s->str[0] == '-' && genrange(s))
	  return(next(s));
	return(1);
  case RANGE:
	if (s->cnt-- == 0) {
	  s->state = NORMAL;
	  return(next(s));
	}
	++s->lastch;
	return(1);
  case SEQUENCE:
	if (s->cnt-- == 0) {
	  s->state = NORMAL;
	  return(next(s));
	}
	return(1);
  case SET:
	if ((s->lastch = s->set[s->cnt++]) == OOBCH) {
	  s->state = NORMAL;
	  return(next(s));
	}
	return(1);
  default:
	return(0);
  }

}
