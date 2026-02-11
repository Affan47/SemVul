get_parameter(char *argument, char *parameter)
{
	while (1)
	{
		switch (argument[0])
		{
		case ' ':
		case '\0':
		case '\t':
		case '\n':
			parameter[0] = '\0';
			return argument;

		default:
			*parameter++ = *argument++;
		}
	}

	return argument;
}
