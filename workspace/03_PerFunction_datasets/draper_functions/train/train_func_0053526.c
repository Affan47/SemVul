spcrc64calctab(unsigned long long *crctab)
{
    unsigned long long v;
    ajint i;
    ajint j;

    for(i=0;i<AJCRC64LEN;++i)
    {
	v = (unsigned long long)i;
	for(j=0;j<8;++j)
	    if(v&1)
#ifndef WIN32
		v = 0xd800000000000000ULL ^ (v>>1);
#else
		v = 0xd800000000000000 ^ (v>>1);
#endif
	    else
		v >>= 1;
	crctab[i] = v;
    }
}
