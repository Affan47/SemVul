build_fake(char *fake, size_t fake_len, int flag, int width, int precision,
    int qualifier, int specifier)
{
    trace(("%s\n", __PRETTY_FUNCTION__));
    char	    *fp;

    fp = fake;
    *fp++ = '%';
    if (flag)
	*fp++ = flag;
    if (width > 0)
    {
	snprintf(fp, fake + fake_len - fp - 5, "%d", width);
	fp += strlen(fp);
    }
    *fp++ = '.';
    snprintf(fp, fake + fake_len - fp - 3, "%d", precision);
    fp += strlen(fp);
    if (qualifier)
	*fp++ = qualifier;
    *fp++ = specifier;
    *fp = 0;
}
