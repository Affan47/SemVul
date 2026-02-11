Set_Ringer_Flags( int condtion, int InOut )
{
	char Char = 0;
	static char RetCode[10];

	if (InOut & RING_INCOMING) Char = 'I';
	else
	if (InOut & RING_OUTGOING) Char = 'O';
	else
	{
		print_msg(PRT_ERR, "Error: Expected flag `I' or `O'!\n");
		return NULL;
	}

	RetCode[0] = Char;

	if (condtion & RING_RING    ) Char = 'R';
	else
	if (condtion & RING_CONNECT ) Char = 'C';
	else
	if (condtion & RING_BUSY    ) Char = 'B';
	else
	if (condtion & RING_AOCD    ) Char = 'A';
	else
	if (condtion & RING_ERROR   ) Char = 'E';
	else
	if (condtion & RING_HANGUP  ) Char = 'H';
	else
	if (condtion & RING_KILL    ) Char = 'K';
	else
	if (condtion & RING_SPEAK   ) Char = 'S';
	else
	if (condtion & RING_PROVIDER) Char = 'P';
	else
	{
		print_msg(PRT_ERR, "Internal error: Unknown flag %d for flag -S!\n",condtion);
		return NULL;
	}

	RetCode[1] = Char;
	RetCode[2] = '\0';

	return RetCode;
}
