NumberOfLeadingZeroes( uint8_t x )
{
	uint8_t y;
	int n;

	n = 8;
	y = x >> 4;  if (y != 0) {n = n - 4;  x = y;}
	y = x >> 2;  if (y != 0) {n = n - 2;  x = y;}
	y = x >> 1;  if (y != 0) return n - 2;
	return (int)(n - x);
}
