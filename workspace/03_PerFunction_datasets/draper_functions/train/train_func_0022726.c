allocCandlist(obj, n)
CannaObject obj;
int n;
{
    ICString *p;
    int i;

    if (n <= obj->canna.candlistsize) return;

    if (obj->canna.candlistsize == 0) {
	p = (ICString *)XtMalloc(n * sizeof(ICString));
    } else {
	p = (ICString *)XtRealloc((char *)obj->canna.candlist,
				  n * sizeof(ICString));
    }
    for (i = obj->canna.candlistsize ; i < n ; i++) {
      p[i].nbytes = p[i].nchars = (unsigned short)0;
      p[i].data = (char *)0;
      p[i].attr = 0;
    }

    obj->canna.candlist = p;
    obj->canna.candlistsize = n;
}
