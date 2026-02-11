micky_to_displacement(unsigned long w)
{
	long d = (long)w ;


	return abs(d) >= double_speed_threshold ? d+d : d;
}
