tbaudrate(char *rate)
{
    const SPEEDS *sp;
    int found = FALSE;


    if (*rate == 'B')
	++rate;

    for (sp = speeds; sp->string; ++sp) {
	if (!CaselessCmp(rate, sp->string)) {
	    found = TRUE;
	    break;
	}
    }
    if (!found)
	err("unknown baud rate %s", rate);
    return (sp->speed);
}
