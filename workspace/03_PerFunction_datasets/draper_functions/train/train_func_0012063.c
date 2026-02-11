write_all_states(char *buff, unsigned int states)
{
	unsigned int lowbit;

	buff[0] = '\0';


	while ((lowbit = states & (1 + ~states)) != 0) {
		states &= ~lowbit;
		strcat(buff, state_name(lowbit));
		if (states != 0)
			strcat(buff, "/");
	}
	return buff;
}
