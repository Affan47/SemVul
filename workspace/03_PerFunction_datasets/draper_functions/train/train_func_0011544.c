isBounceStart(mbox_ctx *mctx, const char *line)
{
	size_t len;

	if(line == NULL)
		return FALSE;
	if(*line == '\0')
		return FALSE;


	len = strlen(line);
	if((len < 6) || (len >= 72))
		return FALSE;

	if((memcmp(line, "From ", 5) == 0) ||
	   (memcmp(line, ">From ", 6) == 0)) {
		int numSpaces = 0, numDigits = 0;

		line += 4;

		do
			if(*line == ' ')
				numSpaces++;
			else if(isdigit((*line) & 0xFF))
				numDigits++;
		while(*++line != '\0');

		if(numSpaces < 6)
			return FALSE;
		if(numDigits < 11)
			return FALSE;
		return TRUE;
	}
	return (bool)(cli_filetype((const unsigned char *)line, len, mctx->ctx->engine) == CL_TYPE_MAIL);
}
