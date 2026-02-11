get_charset(MimeArg *args)
{
    while (args->value)
	if (strcmp(args->name, "charset") == 0)
	    return args->value;
	else
	    args++;

    return NULL;
}
