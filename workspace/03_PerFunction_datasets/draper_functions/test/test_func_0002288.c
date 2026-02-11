des_ecb_encrypt(des_cblock *input, des_cblock *output, long length,
						    des_key_schedule schedule, int enc)
{
	register DES_LONG tin0,tin1;
	register DES_LONG tout0,tout1;
	register unsigned char *in,*out;
	register long l=length;
	DES_LONG tin[2];

	in=(unsigned char *)input;
	out=(unsigned char *)output;

	if (enc)
	{
		for (l-=8; l>=0; l-=8)
		{
			c2l(in,tin0); tin[0]=tin0;
			c2l(in,tin1); tin[1]=tin1;
			des_encrypt((DES_LONG *)tin,schedule,DES_ENCRYPT);
			tout0=tin[0]; l2c(tout0,out);
			tout1=tin[1]; l2c(tout1,out);
		}
		if (l != -8)
		{
			c2ln(in,tin0,tin1,l+8);
			tin[0]=tin0;
			tin[1]=tin1;
			des_encrypt((DES_LONG *)tin,schedule,DES_ENCRYPT);
			tout0=tin[0]; l2c(tout0,out);
			tout1=tin[1]; l2c(tout1,out);
		}
	}
	else
	{
		for (l-=8; l>=0; l-=8)
		{
			c2l(in,tin0); tin[0]=tin0;
			c2l(in,tin1); tin[1]=tin1;
			des_encrypt((DES_LONG *)tin,schedule,DES_DECRYPT);
			tout0=tin[0]; l2c(tout0,out);
			tout1=tin[1]; l2c(tout1,out);
		}
		if (l != -8)
		{
			c2l(in,tin0); tin[0]=tin0;
			c2l(in,tin1); tin[1]=tin1;
			des_encrypt((DES_LONG *)tin,schedule,DES_DECRYPT);
			tout0=tin[0];
			tout1=tin[1];
			l2cn(tout0,tout1,out,l+8);
		}
	}
	tin0=tin1=tout0=tout1=0;
	tin[0]=tin[1]=0;
}
