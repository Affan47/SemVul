execute(const char *cmdline, enum kernel_type type)
{
    com32sys_t ireg;
    const char *p, *const *pp;
    char *q = __com32.cs_bounce;
    const char *kernel, *args;

    memset(&ireg, 0, sizeof ireg);

    kernel = q;
    p = cmdline;
    while (*p && !my_isspace(*p)) {
	*q++ = *p++;
    }
    *q++ = '\0';

    args = q;
    while (*p && my_isspace(*p))
	p++;

    strcpy(q, p);

    if (kernel[0] == '.' && type == KT_NONE) {

	enum kernel_type type = KT_NONE;
	for (pp = kernel_types; *pp; pp++, type++) {
	    if (!strcmp(kernel + 1, *pp)) {
		execute(p, type);
	    }
	}
    }

    if (type == KT_LOCALBOOT) {
	ireg.eax.w[0] = 0x0014;
	ireg.edx.w[0] = strtoul(kernel, NULL, 0);
    } else {
	if (type < KT_KERNEL)
	    type = KT_KERNEL;

	ireg.eax.w[0] = 0x0016;
	ireg.esi.w[0] = OFFS(kernel);
	ireg.ds = SEG(kernel);
	ireg.ebx.w[0] = OFFS(args);
	ireg.es = SEG(args);
	ireg.edx.l = type - KT_KERNEL;

    }

    __intcall(0x22, &ireg, NULL);


}
