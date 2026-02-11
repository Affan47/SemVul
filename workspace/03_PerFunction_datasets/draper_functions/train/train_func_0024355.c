Devices_GetIOCB(void)
{
	if ((CPU_regX & 0x8f) != 0) {
		CPU_regY = 134;
		CPU_SetN;
		return FALSE;
	}
	h_iocb = CPU_regX >> 4;
	return TRUE;
}
