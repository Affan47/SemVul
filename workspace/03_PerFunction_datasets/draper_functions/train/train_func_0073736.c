output_attlist(struct protstream *pout, struct attvaluelist *l)
{
    int flag = 0;

    assert(l);

    prot_putc('(',pout);

    while(l) {
	if (flag) prot_putc(' ', pout);
	else flag = 1;

	prot_printstring(pout, l->attrib);
	prot_putc(' ', pout);
	prot_printstring(pout, l->value);

	l = l->next;
    }

    prot_putc(')',pout);
}
