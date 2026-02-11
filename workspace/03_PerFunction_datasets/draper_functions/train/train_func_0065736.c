hexchar( unsigned int b )
{
	if (b < 10)
		return '0' + b;
	return 'a' + (b - 10);
}
