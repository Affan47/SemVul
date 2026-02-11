register_zone(int cpunum, UINT32 start, UINT32 end)
{
	char name[256];
	sprintf (name, "%08x-%08x", start, end);
	switch (cpunum_databus_width(cpunum))
	{
	case 8:
		state_save_register_UINT8 ("memory", cpunum, name, memory_find_base(cpunum, start), end-start+1);
		break;
	case 16:
		state_save_register_UINT16("memory", cpunum, name, memory_find_base(cpunum, start), (end-start+1)/2);
		break;
	case 32:
		state_save_register_UINT32("memory", cpunum, name, memory_find_base(cpunum, start), (end-start+1)/4);
		break;
	}
}
