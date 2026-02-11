more_output(z)
const char *z;
{
	if (crows > 0  &&  coutput > crows - 2) {
		printf("Press return to continue: ");
		(void) fflush(stdout);
		while (getchar() != '\n')
			;
		coutput = 0;
	}

	if (z != NULL)
		printf("%s\n", z);

	coutput++;
}
