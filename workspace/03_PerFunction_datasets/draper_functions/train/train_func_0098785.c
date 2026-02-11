Infoclr_Opcode(const char *str)
{
	register int i;


	for (i = 0; opcode_pairs[i*2]; ++i)
	{

		if (streq(opcode_pairs[i*2], str))
		{

			return (atoi(opcode_pairs[i*2+1]));
		}
	}


	return (-1);
}
