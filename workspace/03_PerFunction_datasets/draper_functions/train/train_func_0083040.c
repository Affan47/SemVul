utf16_to_utf8(char* output, const le16_t* input, size_t outsize,
		size_t insize)
{
	const le16_t* inp = input;
	char* outp = output;
	wchar_t wc;

	while (inp - input < insize && le16_to_cpu(*inp))
	{
		inp = utf16_to_wchar(inp, &wc, insize - (inp - input));
		if (inp == NULL)
		{
			exfat_error("illegal UTF-16 sequence");
			return -EILSEQ;
		}
		outp = wchar_to_utf8(outp, wc, outsize - (outp - output));
		if (outp == NULL)
		{
			exfat_error("name is too long");
			return -ENAMETOOLONG;
		}
	}
	*outp = '\0';
	return 0;
}
