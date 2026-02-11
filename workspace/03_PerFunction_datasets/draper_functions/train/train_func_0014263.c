targa_copy_data(char *to, char *from, int pixels, int fromsize, int tosize)
{
	if ( (fromsize == 2) && (tosize==2) )	{

		ushort *src, *dst;

		src = (ushort *)from;
		dst = (ushort *)from;
		for (int i=0; i<pixels; i++ )	{
			*dst++ = (ushort)((*src++) ^ 0x8000);
		}
		return tosize*pixels;
	} else if ( (fromsize == 2) && (tosize == 3) )	{
		ushort *src;

		src = (ushort *)from;
		for (int i=0; i<pixels; i++ )	{
			ushort pixel = *src++;

			*to++ = (ubyte)((pixel & 0x1f) * 8);
			*to++ = (ubyte)(((pixel >> 5) & 63) * 4);
			*to++ = (ubyte)(((pixel >> 11) & 0x1f) * 8);
		}
		return tosize*pixels;
	} else {
		Assert(fromsize == tosize);
		memcpy(to, from, pixels * fromsize);
		return tosize*pixels;
	}
}
