sffmtint(const char *str, int *v)
#else
static char *sffmtint(str, v)
char *str;
int *v;
#endif
{
    for (*v = 0; isdigit(*str); ++str)
	*v = *v * 10 + (*str - '0');
    *v -= 1;
    return (char *) str;
}
