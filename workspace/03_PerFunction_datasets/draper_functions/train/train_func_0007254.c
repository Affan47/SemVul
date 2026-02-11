append(const wchar_t *s, size_t n)
{
    while (n > 0)
    {
	append(*s++);
	--n;
    }
}
