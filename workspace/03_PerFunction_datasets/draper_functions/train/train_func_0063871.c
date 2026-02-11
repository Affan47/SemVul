local_flush(message_t *message)
{
	char buffer[BUFSIZ];
	size_t n;

	do {
		n = message_read(message, buffer, BUFSIZ);
		if(ferror(mda_fp))
		{
			perror(NULL);
			exit(EX_OSERR);
		}
	} while(n == BUFSIZ);
}
