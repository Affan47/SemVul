decode(string s)
{
	if (decoder)
		decoder->decode(s);
	else
		decoded(s);
}
