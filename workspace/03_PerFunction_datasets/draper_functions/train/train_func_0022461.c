GET_MEM_ADDR(UINT16 DMA)
{
	if (R.opcode.b.l & 0x80)
		memaccess = IND;
	else
		memaccess = DMA;
}
