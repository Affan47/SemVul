getdictionarycode(void)
{
	if (unpackcount!=8) return unpackbuf[unpackcount++];
	else
	{

		L9BYTE d1=*dictptr++,d2;
		unpackbuf[0]=d1>>3;
		d2=*dictptr++;
		unpackbuf[1]=((d2>>6) + (d1<<2)) & 0x1f;
		d1=*dictptr++;
		unpackbuf[2]=(d2>>1) & 0x1f;
		unpackbuf[3]=((d1>>4) + (d2<<4)) & 0x1f;
		d2=*dictptr++;
		unpackbuf[4]=((d1<<1) + (d2>>7)) & 0x1f;
		d1=*dictptr++;
		unpackbuf[5]=(d2>>2) & 0x1f;
		unpackbuf[6]=((d2<<3) + (d1>>5)) & 0x1f;
		unpackbuf[7]=d1 & 0x1f;
		unpackcount=1;
		return unpackbuf[0];
	}
}
