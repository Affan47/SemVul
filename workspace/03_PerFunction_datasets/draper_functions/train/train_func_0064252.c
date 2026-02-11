cancelWhen(n, tag)
  register nptr  n;
  int *tag;
{
    awptr p, plast;

    if (n->awpending) {
       plast = NULL;
       for (p = n->awpending; p != NULL; p = p->nxt) {
	  if (p->tag == *tag) {
	     free(p->proc);
	     if (plast == NULL)
		n->awpending = p->nxt;
	     else
		plast->nxt = p->nxt;
	     Ffree(p);
	     return -1;
	  }
	  plast = p;
       }
    }
    return 0;
}
