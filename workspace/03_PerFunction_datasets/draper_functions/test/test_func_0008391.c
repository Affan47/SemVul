DXAllocateZero(unsigned int n)
{
    Pointer p;
    if (n==0)
	n++;
    p = (Pointer)sh_malloc(n);
    if (!p)
	DXSetError(ERROR_NO_MEMORY, "#13000");
    memset(p, '\0', n);
    return p;
}
