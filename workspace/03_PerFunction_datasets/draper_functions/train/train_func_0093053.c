bscope_blur_8(guchar *ptr,gint w, gint h, gint bpl)
{
	register guint i,sum;
	register guchar *iptr;

	iptr = ptr + bpl + 1;
	i = bpl * h;
	while(i--)
	{
		sum = (iptr[-bpl] + iptr[-1] + iptr[1] + iptr[bpl]) >> 2;
		if(sum > 2)
			sum -= 2;
		*(iptr++) = sum;
	}


}
