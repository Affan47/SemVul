get_int_lsb_first (FILE *f, unsigned int sz, unsigned int *val)
{
    int ch, i;

    *val = 0;
    for (i = 0; i < sz; i++) {
	ch = fgetc(f);
	if (feof(f))
	    return FALSE;
	*val |= (ch << 8*i);
    }
    return TRUE;
}
