opOUTbi_B_BB (int opcode)
{
	CINEBYTE temp_byte = opcode & 0x07;

	if (temp_byte - 0x06)
		return opOUTsnd_B (opcode);

	vgColour = ((register_B & 0x01) << 3) | 0x07;

	return state_BB;
}
