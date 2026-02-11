agxbput(char *s, agxbuf * xb)
{
    unsigned int ssz = strlen(s);
    if (xb->ptr + ssz > xb->eptr)
	agxbmore(xb, ssz);
    memcpy(xb->ptr, s, ssz);
    xb->ptr += ssz;
    return ssz;
}
