CALCULATE_ADD_DIGITCARRY(void)
{
	if (((UINT8)(old_data) & 0x0f) > ((UINT8)(R.ALU) & 0x0f)) {
		SET(DC_FLAG);
	}
	else {
		CLR(DC_FLAG);
	}
}
