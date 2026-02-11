read_keys(keys)
    int keys;
{
    char *contents;
    char key_seq[80];
    int i, j, need_conversion;


    for (i = keys; i < MAX_KEYS; i++)
    {
	configuration_getvarinfo(key_seq, &contents, 1, NO_SEEK);

	if (*key_seq == 0)
	    break;

	if (*key_seq != '^')
	{
	    char *key_seq_ptr = tty_get_symbol_key_seq(key_seq);

	    if (key_seq_ptr)
	    {

		if (*key_seq_ptr == '\0')
		    continue;


		strcpy(key_seq, key_seq_ptr);
		need_conversion = 0;
	    }
	    else
	    {


		need_conversion = 1;
	    }
	}
	else
	    need_conversion = 1;

	if (contents == NULL)
	    continue;

	for (j = 0; j < BUILTIN_OPERATIONS; j++)
	    if (strcmp(contents, built_in[j]) == 0)
		break;

	if (j < BUILTIN_OPERATIONS)
	{
	    if (!need_conversion ||
		tty_key_human2machine((unsigned char *)key_seq))
		tty_key_list_insert((unsigned char *)key_seq,  built_in[-j-1]);
	}
	else
	    fprintf(stderr, "%s: invalid built-in operation: %s.\n",
		    g_program, contents);
    }

    return i;
}
