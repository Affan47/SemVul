getstring(char **data, int *datalen, char **p, int *length)
{
    *p = NULL;
    if (*datalen < 4)
	return;
    *length = GET_32BIT(*data);
    if (*length < 0)
        return;
    *datalen -= 4;
    *data += 4;
    if (*datalen < *length)
	return;
    *p = *data;
    *data += *length;
    *datalen -= *length;
}
