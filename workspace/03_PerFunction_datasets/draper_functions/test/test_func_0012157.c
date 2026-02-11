readtonl(FILE *fp)
{
    int input_buffer;

    while (1) {
	if ((input_buffer = fgetc(fp)) == EOF) return EOF;
	if (input_buffer == '\n') {
	    return FALSE;
	}
    }
    return TRUE;
}
