is_power_of_two(int w, int h)
{
	return ( (w && !(w & (w-1))) && (h && !(h & (h-1))) );
}
