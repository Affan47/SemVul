UT_UnixAssertMsg(const char * szMsg, const char * szFile, int iLine)
{
	static int count = 0;

	printf("\n");
	printf("**** (%d) Assert ****\n", ++count);
	printf("**** (%d) %s at %s:%d ****\n", count,szMsg,szFile,iLine);

	while (1)
	{
		printf("**** (%d) Continue? (y)es/(n)o/(i)gnore/(b)reak [y] : ", count);
		fflush(stdout);

		char buf[10];
		memset(buf,0,10);

		fgets(buf,10,stdin);

		switch (buf[0])
		{
		case '\0':
		case '\n':
		case 'y':
		case 'Y':
			return 1;

		case 'n':
		case 'N':
			abort();
			return 0;

		case 'i':
		case 'I':
			return -1;

		case 'b':
		case 'B':
			if (break_into_debugger())
				return 1;
			else
				printf("**** No debugger attached\n");

		default:
			break;
		}
	}
}
