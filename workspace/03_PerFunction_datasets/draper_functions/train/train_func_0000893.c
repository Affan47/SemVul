dent(int n)
{
    if(sindent == NULL) {
	sindent = (char*)ocmalloc(102);
	MEMCHECK(sindent,NULL);
	memset((void*)sindent,(int)' ',(size_t)101);
	sindent[101] = '\0';
    }
    if(n > 100) n = 100;
    return sindent+(100-n);
}
