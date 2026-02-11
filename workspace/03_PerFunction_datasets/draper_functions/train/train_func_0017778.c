gvl_read_char(int pos, const unsigned char *data)
{
    if (!data)
	return '\0';

    return data[pos];
}
