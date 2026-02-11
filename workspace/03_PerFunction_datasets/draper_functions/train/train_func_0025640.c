callback_func(const char *c, size_t n, void *va)
{
	((mail::Attachment *)va)->encoded += string(c, c+n);
	return 0;
}
