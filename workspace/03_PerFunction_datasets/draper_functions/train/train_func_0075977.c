ruby_each_words(const char *str, void (*func)(const char*, int, void*), void *arg)
{
    const char *end;
    int len;

    if (!str) return;
    for (; *str; str = end) {
	while (ISSPACE(*str) || *str == ',') str++;
	if (!*str) break;
	end = str;
	while (*end && !ISSPACE(*end) && *end != ',') end++;
	len = (int)(end - str);
	(*func)(str, len, arg);
    }
}
