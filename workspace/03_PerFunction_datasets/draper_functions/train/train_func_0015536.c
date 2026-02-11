num_error(printopt, errp)
	char *printopt;
	int *errp;
{
	PARG parg;

	if (errp != NULL)
	{
		*errp = TRUE;
		return (-1);
	}
	if (printopt != NULL)
	{
		parg.p_string = printopt;
		error("Number is required after %s", &parg);
	}
	return (-1);
}
