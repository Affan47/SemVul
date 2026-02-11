check_other_key(object l, int n, ...)
{
	va_list ap;
	object other_key = OBJNULL;
	object k;
	int i;
	bool allow_other_keys = FALSE;

	for (;  !endp(l);  l = l->c.c_cdr->c.c_cdr) {
		k = l->c.c_car;
		if (!keywordp(k))
		  FEunexpected_keyword(k);
		if (endp(l->c.c_cdr))

		  FEunexpected_keyword(Cnil);
		if (k == sKallow_other_keys && l->c.c_cdr->c.c_car != Cnil) {
			allow_other_keys = TRUE;
		} else {
		  char buf [100];
		  bzero(buf,n);
		  va_start(ap,n);
		  for (i = 0;  i < n;  i++)
		    { if (va_arg(ap,object) == k &&
			  buf[i] ==0) {buf[i]=1; break;}}
		  va_end(ap);
		  if (i >= n) other_key = k;
		}
	}
	if (other_key != OBJNULL && !allow_other_keys)
	  FEunexpected_keyword(other_key);
}
