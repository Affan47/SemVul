Enc64(Enc64_t * this, unsigned char *dest, int maxlen, int *len)
{


	int	l;
	unsigned char *	s;
	unsigned char *	d;
	int	reml;
	int	i;

	if (!this->slen)
		return 1;
	l = this->slen / 3;
	s = this->source;
	if (l > maxlen / 4)
	{
		l = maxlen / 4;
		this->slen -= l*3;
		reml = 0;
		this->source += l*3;
		}
	else
	{
		reml = this->slen % 3;
		this->slen = 0;
		}
	for (d = dest, i = 0; i < l; i++)
	{
		*d++ = b64[(*s >> 2) & 0x3f];
		*d++ = b64[((*s << 4) & 0x30) + ((*(s+1) >> 4) & 0x0f)];
		s++;
		*d++ = b64[((*s << 2) & 0x3c) + ((*(s+1) >> 6) & 0x03)];
		s++;
		*d++ = b64[*s & 0x3f];
		s++;
		}
	if (reml--)
		*d++ = b64[(*s >> 2) & 0x3f];
	else
	{
		*d = 0;
		*len = l*4;
		return 0;
		}
	if (reml)
	{
		*d++ = b64[((*s << 4) & 0x30) + ((*(s+1) >> 4) & 0x0f)];
		s++;
		*d++ = b64[((*s << 2) & 0x3c)];
		}
	else
	{
		*d++ = b64[((*s << 4) & 0x30) + ((*(s+1) >> 4) & 0x0f)];
		*d++ = '=';
		}
	*d++ = '=';
	*d = 0;
	*len = (l+1)*4;
	return 0;
	}
