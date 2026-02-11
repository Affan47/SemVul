wrt_I(Uint *n, int w, ftnlen len, register int base)
#endif
{	int ndigit,sign,spare,i;
	longint x;
	char *ans;
	if(len==sizeof(integer)) x=n->il;
	else if(len == sizeof(char)) x = n->ic;
#ifdef Allow_TYQUAD
	else if (len == sizeof(longint)) x = n->ili;
#endif
	else x=n->is;
	ans=f__icvt(x,&ndigit,&sign, base);
	spare=w-ndigit;
	if(sign || f__cplus) spare--;
	if(spare<0)
		for(i=0;i<w;i++) (*f__putn)('*');
	else
	{	for(i=0;i<spare;i++) (*f__putn)(' ');
		if(sign) (*f__putn)('-');
		else if(f__cplus) (*f__putn)('+');
		for(i=0;i<ndigit;i++) (*f__putn)(*ans++);
	}
	return(0);
}
