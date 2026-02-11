print_icmp_code (int type, int code, char *prefix)
{
  struct icmp_code_descr *p;

  for (p = icmp_code_descr; p < icmp_code_descr + NITEMS (icmp_code_descr);
       p++)
    if (p->type == type && p->code == code)
      {
	printf ("%s\n", p->diag);
	return;
      }

  printf ("%s, Unknown Code: %d\n", prefix, code);
}
