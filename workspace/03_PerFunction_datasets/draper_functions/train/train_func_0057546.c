hexstr(guint8 *p, int len)
{
    char *result = NULL;
    int i;

    for (i = 0; i < len; i++) {
	if (result)
	    result = newvstrallocf(result, "%s %02x", result, (guint)(*(p++)));
	else
	    result = vstrallocf("[%02x", (guint)(*(p++)));
    }
    result = newvstrallocf(result, "%s]", result);

    return result;
}
