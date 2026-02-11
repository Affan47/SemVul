opOUT16_B_BB (int opcode)
{
	CINEBYTE temp_byte = opcode & 0x07;

	if (temp_byte - 0x06)
		return opOUTsnd_B (opcode);

	if ((register_B & 0xFF) != 1)
	{
		vgColour = FromX & 0x0F;

		if (!vgColour)
			vgColour = 1;
	}

	return state_BB;
}
