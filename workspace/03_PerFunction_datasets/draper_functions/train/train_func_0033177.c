puts(const char *s)
{
    int count = 0;

    while (*s) {
	putchar(*s);
	count++;
	s++;
    }

    return count;
}
