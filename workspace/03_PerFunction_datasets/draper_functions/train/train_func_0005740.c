readint(const char *arg)
{
    int val;
    char *endptr;

    val = strtol(arg, &endptr, 10);
    if ((*arg == '\0') || (*endptr != '\0')) {
	usage(stderr, 1);
    }

    return val;
}
