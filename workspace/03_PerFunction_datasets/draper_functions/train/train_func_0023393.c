power_of_two(unsigned int v)
{
	unsigned i;
	for(i=0;i<(sizeof(v)*8);i++) {
		if((((unsigned int)1)<<i)==v)
			return 1;
	}
	return 0;
}
