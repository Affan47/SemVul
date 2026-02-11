sk_insert(_STACK *st, void *data, int loc)
	{
	char **s;

	if(st == NULL) return 0;
	if (st->num_alloc <= st->num+1)
		{
		s=OPENSSL_realloc((char *)st->data,
			(unsigned int)sizeof(char *)*st->num_alloc*2);
		if (s == NULL)
			return(0);
		st->data=s;
		st->num_alloc*=2;
		}
	if ((loc >= (int)st->num) || (loc < 0))
		st->data[st->num]=data;
	else
		{
		int i;
		char **f,**t;

		f=st->data;
		t=&(st->data[1]);
		for (i=st->num; i>=loc; i--)
			t[i]=f[i];

#ifdef undef
		memmove(&(st->data[loc+1]),
			&(st->data[loc]),
			sizeof(char *)*(st->num-loc));
#endif
		st->data[loc]=data;
		}
	st->num++;
	st->sorted=0;
	return(st->num);
	}
