read_n(SSL *s, unsigned int n, unsigned int max,
	     unsigned int extend)
	{
	int i,off,newb;


	if (s->s2->rbuf_left >= (int)n)
		{
		if (extend)
			s->packet_length+=n;
		else
			{
			s->packet= &(s->s2->rbuf[s->s2->rbuf_offs]);
			s->packet_length=n;
			}
		s->s2->rbuf_left-=n;
		s->s2->rbuf_offs+=n;
		return(n);
		}

	if (!s->read_ahead) max=n;
	if (max > (unsigned int)(SSL2_MAX_RECORD_LENGTH_2_BYTE_HEADER+2))
		max=SSL2_MAX_RECORD_LENGTH_2_BYTE_HEADER+2;


	off=0;
	if ((s->s2->rbuf_left != 0) || ((s->packet_length != 0) && extend))
		{
		newb=s->s2->rbuf_left;
		if (extend)
			{
			off=s->packet_length;
			if (s->packet != s->s2->rbuf)
				memcpy(s->s2->rbuf,s->packet,
					(unsigned int)newb+off);
			}
		else if (s->s2->rbuf_offs != 0)
			{
			memcpy(s->s2->rbuf,&(s->s2->rbuf[s->s2->rbuf_offs]),
				(unsigned int)newb);
			s->s2->rbuf_offs=0;
			}
		s->s2->rbuf_left=0;
		}
	else
		newb=0;


	s->packet=s->s2->rbuf;
	while (newb < (int)n)
		{
		clear_sys_error();
		if (s->rbio != NULL)
			{
			s->rwstate=SSL_READING;
			i=BIO_read(s->rbio,(char *)&(s->s2->rbuf[off+newb]),
				max-newb);
			}
		else
			{
			SSLerr(SSL_F_READ_N,SSL_R_READ_BIO_NOT_SET);
			i= -1;
			}
#ifdef PKT_DEBUG
		if (s->debug & 0x01) sleep(1);
#endif
		if (i <= 0)
			{
			s->s2->rbuf_left+=newb;
			return(i);
			}
		newb+=i;
		}


	if (newb > (int)n)
		{
		s->s2->rbuf_offs=n+off;
		s->s2->rbuf_left=newb-n;
		}
	else
		{
		s->s2->rbuf_offs=0;
		s->s2->rbuf_left=0;
		}
	if (extend)
		s->packet_length+=n;
	else
		s->packet_length=n;
	s->rwstate=SSL_NOTHING;
	return(n);
	}
