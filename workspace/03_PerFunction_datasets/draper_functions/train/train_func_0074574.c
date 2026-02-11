useropt_exec(Jconf *jconf, char *argv[], int argc, int *n)
{
  USEROPT *x;
  int narg, i;

  for(x=useropt_root;x;x=x->next) {
    if (strmatch(argv[*n], x->optstr)) {
      i = *n + 1;
      while(i < argc && (argv[i][0] != '-' || (argv[i][1] >= '0' && argv[i][1] <= '9'))) i++;

      narg = i - *n - 1;
      if (narg > x->argnum || narg < x->reqargnum) {
	if (x->reqargnum != x->argnum) {
	  jlog("ERROR: useropt_exec: \"%s\" should have at least %d argument(s)\n", x->optstr, x->reqargnum);
	} else {
	  jlog("ERROR: useropt_exec: \"%s\" should have %d argument(s)\n", x->optstr, x->argnum);
	}
	return -1;
      }

      if ((*(x->func))(jconf, &(argv[(*n)+1]), narg) == FALSE) {
	jlog("ERROR: useropt_exec: \"%s\" function returns FALSE\n", x->optstr);
	return -1;
      }
      *n += narg;
      return 1;
    }
  }

  return 0;
}
