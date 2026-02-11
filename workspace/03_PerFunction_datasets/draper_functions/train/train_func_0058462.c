getLastNamedIndex ( void )
{
	int i;

	for (i = stackIndex - 1; i >= 0; --i)
	{
        if (vStringLength (stack[i].contextName) > 0)
		{
			return i;
		}
	}

	return -1;
}
