in_commasep_string(char *needle, char *haystack, int haylen)
{
    int needlen;
    if (!needle || !haystack)
	return 0;
    needlen = strlen(needle);
    while (1) {


	if (haylen >= needlen &&
	    !memcmp(needle, haystack, needlen) &&
	    (haylen == needlen || haystack[needlen] == ',')

	    )
	    return 1;


	while (haylen > 0 && *haystack != ',')
	    haylen--, haystack++;
	if (haylen == 0)
	    return 0;
	haylen--, haystack++;
    }
}
