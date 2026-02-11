wrt_A(char *p, ftnlen len)
#endif
{
	while(len-- > 0) (*f__putn)(*p++);
	return(0);
}
