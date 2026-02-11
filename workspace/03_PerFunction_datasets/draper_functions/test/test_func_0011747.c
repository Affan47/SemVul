acdCountType(const char* type)
{
    ajint ret = 0;
    AcdPAcd pa;
    ajint itype = 0;

    itype = acdFindTypeC(type);

    for(pa=acdList; pa; pa=pa->Next)
    {
	if(pa->Type == itype) ret++;
    }

    return ret;
}
