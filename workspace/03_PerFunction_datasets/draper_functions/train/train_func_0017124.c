opOUTWW_A_A (int opcode)
{
	if ((opcode & 0x07) != 6)
		return opOUTsnd_A (opcode);

	if ((register_A & 0x1) == 1)
	{
		CINEWORD temp_word = ~FromX & 0x0FFF;
		if (!temp_word)
			vgColour = 0;
		else
		{
			if (temp_word & 0x0888)

				vgColour = ((temp_word >> 1) & 0x04) | ((temp_word >> 6) & 0x02) | ((temp_word >> 11) & 0x01) | 0x08;
			else if (temp_word & 0x0444)

				vgColour = (temp_word & 0x04) | ((temp_word >> 5) & 0x02) | ((temp_word >> 10) & 0x01);
		}
	}

	return state_A;
}
