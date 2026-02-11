KTSetErrorMsg (char *msg, char *str)


{
	if (error_msg)
	{
		free (error_msg);
	}
	if (asprintf (&error_msg, msg, str) == -1)
	{
		fprintf (stderr, "keytouch-editor: Did not have enough memory for "
		                 "copying the following error message:\n   ");
		fprintf (stderr, msg, str);
		putc ('\n', stderr);
		error_msg = NULL;
	}
}
