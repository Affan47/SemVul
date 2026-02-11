encode_ContextFlags(unsigned char *p, size_t len, const ContextFlags *data, size_t *size)
{
size_t ret = 0;
size_t l;
int i, e;

i = 0;
{
unsigned char c = 0;
*p-- = c; len--; ret++;
c = 0;
*p-- = c; len--; ret++;
c = 0;
*p-- = c; len--; ret++;
c = 0;
if(data->integFlag) c |= 1<<1;
if(data->confFlag) c |= 1<<2;
if(data->anonFlag) c |= 1<<3;
if(data->sequenceFlag) c |= 1<<4;
if(data->replayFlag) c |= 1<<5;
if(data->mutualFlag) c |= 1<<6;
if(data->delegFlag) c |= 1<<7;
*p-- = c;
*p-- = 0;
len -= 2;
ret += 2;
}

e = der_put_length_and_tag (p, len, ret, UNIV, PRIM,UT_BitString, &l);
BACK;
*size = ret;
return 0;
}
