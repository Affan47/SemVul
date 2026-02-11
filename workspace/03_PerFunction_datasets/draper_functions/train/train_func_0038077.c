getSegLen (char* s)
{
    char* p = strchr (s, ';');
    char* endp;
    double v;

    if (!p) {
	return 0;
    }
    *p++ = '\0';
    v = strtod (p, &endp);
    if (endp != p) {
	if (v >= 0)
	    return v;
    }
    return -1;
}
