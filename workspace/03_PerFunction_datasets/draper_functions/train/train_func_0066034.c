Perl_savepvn(pTHX_ const char *pv, I32 len)
{
    char *newaddr;
    PERL_UNUSED_CONTEXT;

    assert(len >= 0);

    Newx(newaddr,len+1,char);

    if (pv) {

    	newaddr[len] = '\0';
    	return (char *) CopyD(pv,newaddr,len,char);
    }
    else {
	return (char *) ZeroD(newaddr,len+1,char);
    }
}
