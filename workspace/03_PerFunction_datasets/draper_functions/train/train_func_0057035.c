install(keyptr, data)
register char *keyptr;
unsigned char data;
{
    char lowcasebuf[20];
    unsigned namelength;
    char *nameptr;
    char *namend;
    register struct sym_s *symptr;

    while (*keyptr != 0)
    {
	namelength = *keyptr++;
	lineptr = (symname = keyptr) + namelength;
	for (nameptr = lowcasebuf, namend = lowcasebuf + namelength;
	     nameptr < namend;)
	{
	    if (*keyptr < 'A' || *keyptr > 'Z')
		*nameptr++ = *keyptr++;
	    else
		*nameptr++ = *keyptr++ + ('a' - 'A');
	}
	symptr = lookup();
	symptr->type = MNREGBIT;
	symptr->data = data;
	symptr->value_reg_or_op.op.routine = *keyptr;
	symptr->value_reg_or_op.op.opcode = keyptr[1];
	lineptr = (symname = lowcasebuf) + namelength;
	symptr = lookup();
	symptr->type = MNREGBIT;
	symptr->data = data;
	symptr->value_reg_or_op.op.routine = *keyptr;
	symptr->value_reg_or_op.op.opcode = keyptr[1];
	keyptr += 2;
    }
}
