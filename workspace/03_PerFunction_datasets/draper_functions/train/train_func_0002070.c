add_bits(CByteArray *data, unsigned long *bit_pos, unsigned long pattern, unsigned int pattern_length)
{
	unsigned long i;

	for(i=0;i<pattern_length;i++)
	{
		data=add_bit(data,bit_pos,(unsigned char)((pattern>>(pattern_length-1-i))&1) );
	}
	return data;
}
