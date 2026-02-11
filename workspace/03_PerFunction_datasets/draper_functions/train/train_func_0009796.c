DXNewMeshArray(int n, ...)
{
    Array terms[100];
    int i;
    va_list arg;

    ASSERT(n<100);


    va_start(arg,n);
    for (i=0; i<n; i++)
	terms[i] = va_arg(arg, Array);
    va_end(arg);


    return DXNewMeshArrayV(n, terms);
}
