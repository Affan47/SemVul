pathbin(void)
{
    register char *bin;

    static char *val;

    if ((!(bin = getenv("PATH")) || !*bin) && !(bin = val)) {
	bin = "/bin:/usr/bin:/usr/local/bin";
	val = bin;
    }
    return bin;
}
