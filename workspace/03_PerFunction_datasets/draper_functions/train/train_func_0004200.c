st_strhash(char *string, int modulus)
{
    int val = 0;
    int c;

    while ((c = *string++) != '\0') {
	val = val*997 + c;
    }

    return ((val < 0) ? -val : val)%modulus;

}
