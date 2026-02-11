sattrib(Object o, struct prt_info *p)
{
    Object subo;
    char *name;
    int i;

    for (i=0; (subo=DXGetEnumeratedAttribute(o, i, &name)); i++) {
	p->level++;
	Object_Summary(subo, p);
	p->level--;
    }

}
