UArray_asNumberArrayString(const UArray *self)
{
	UArray *out = UArray_new();
	UArray_setEncoding_(out, CENCODING_ASCII);

	UARRAY_INTFOREACH(self, i, v,
		char s[128];

		if(UArray_isFloatType(self))
		{
			sprintf(s, "%f", (double)v);
		}
		else
		{
			sprintf(s, "%i", (int)v);
		}

		if(i != UArray_size(self) -1 ) strcat(s, ", ");
		UArray_appendBytes_size_(out, (unsigned char *)s, strlen(s));
	);

	return out;
}
