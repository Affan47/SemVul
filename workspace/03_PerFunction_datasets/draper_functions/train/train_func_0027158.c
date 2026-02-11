read_capability(isieve_t *obj)
{
  lexstate_t state;
  char *cap = NULL;

  obj->version = NEW_VERSION;

  while (yylex(&state,obj->pin)==STRING)
  {
      char *attr = string_DATAPTR(state.str);
      char *val;

      val = NULL;

      if (yylex(&state,obj->pin)==' ')
      {
	  if (yylex(&state,obj->pin)!=STRING)
	  {
	      parseerror("STRING");
	  }
	  val = xstrdup(string_DATAPTR(state.str));
	  if (yylex(&state,obj->pin)!=EOL)
	  {
	      parseerror("EOL1");
	  }
      }

      if (strcasecmp(attr,"SASL")==0)
      {
	free(cap);
	cap = val ? xstrdup(val) : NULL;
      } else if (strcasecmp(attr,"SIEVE")==0) {

      } else if (strcasecmp(attr,"IMPLEMENTATION")==0) {

      } else if (strcasecmp(attr,"STARTTLS")==0) {

      } else if (val && strncmp(val,"SASL=",5)==0) {
	  int len = strlen(val);
	  obj->version = OLD_VERSION;
	  free(cap);
	  cap = (char *) xmalloc(len+1);
	  memset(cap, '\0', len);
	  memcpy(cap, val+5, len-6);
	  free(val);
	  return cap;
      } else {

      }
      free(val);
  }

  if (yylex(&state,obj->pin)!=EOL)
  {
      parseerror("EOL2");
  }

  return cap;
}
