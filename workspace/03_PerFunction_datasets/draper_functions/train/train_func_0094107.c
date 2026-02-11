git__strncasecmp(const char *a, const char *b, size_t sz)
{
	int al, bl;

	do {
		al = (unsigned char)tolower(*a);
		bl = (unsigned char)tolower(*b);
		++a, ++b;
	} while (--sz && al && al == bl);

	return al - bl;
}
