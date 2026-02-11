save_shifts()
{
    register shifts *p;
    register short *sp1;
    register short *sp2;
    register short *send;

    p = (shifts *) allocate((unsigned) (sizeof(shifts) +
			(nshifts - 1) * sizeof(short)));

    p->number = this_state->number;
    p->nshifts = nshifts;

    sp1 = shiftset;
    sp2 = p->shift;
    send = shiftset + nshifts;

    while (sp1 < send)
	*sp2++ = *sp1++;

    if (last_shift)
    {
	last_shift->next = p;
	last_shift = p;
    }
    else
    {
	first_shift = p;
	last_shift = p;
    }
}
