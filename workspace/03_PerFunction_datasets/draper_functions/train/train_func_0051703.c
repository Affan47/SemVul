matching_opts (const char *options, const char *test_opts) {
     const char *p, *r;
     char *q;
     int len, this_len;

     if (test_opts == NULL)
	  return 1;
     if (options == NULL)
	  options = "";

     len = strlen(test_opts);
     q = alloca(len+1);
     if (q == NULL)
          die (EX_SYSERR, _("not enough memory"));

     for (p = test_opts; p < test_opts+len; p++) {
	  r = strchr(p, ',');
	  if (r) {
	       this_len = r-p;
	  } else {
	       this_len = strlen(p);
	  }
	  if (!this_len) continue;
	  strncpy(q, p, this_len);
	  q[this_len] = '\0';
	  if (!check_option(options, q))
	       return 0;
	  p += this_len;
     }


     return 1;
}
