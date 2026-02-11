GetLittleShort(void)
{
	int16 val;

    if( data_p + 2 > iff_end ) {
        return -1;
    }

	val = data_p[0];
	val |= data_p[1] << 8;
	data_p += 2;
	return val;
}
