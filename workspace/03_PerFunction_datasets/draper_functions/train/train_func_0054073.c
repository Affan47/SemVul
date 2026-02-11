cycle_EA(short reg, short mode)
{
	if(mode == 7) return cycle_EA_lookup[reg+7];
	return cycle_EA_lookup[mode];
}
