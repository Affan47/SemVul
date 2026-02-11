Buf_StripNewlines(Buffer *bp)
{
	char *ptr = bp->end;


	if (ptr != bp->buf) {
		if (*(ptr - 1) == '\n') {

			*(ptr - 1) = '\0';
			--bp->end;
		}
		--ptr;
	}


	while (ptr != bp->buf) {
		if (*ptr == '\n') {
			*ptr = ' ';
		}
		--ptr;
	}
}
