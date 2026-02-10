real2complex(int count, Pointer from, Pointer to, int itemsize)
{
    int i;
    Pointer efrom, eto;

    efrom = INC(from, itemsize * (count-1));
    eto = INC(to, 2 * itemsize * (count-1));
    for (i=count; i>0; i--) {
	memset(eto, '\0', itemsize);
	eto = DEC(to, itemsize);
	memcpy(efrom, eto, itemsize);
	efrom = DEC(from, itemsize);
	eto = DEC(to, itemsize);
    }

    return OK;
}
