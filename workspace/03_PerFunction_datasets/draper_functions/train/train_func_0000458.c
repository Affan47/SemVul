vgdbOut(const char *fmt, va_list args)
{


    static bool reentered = false;

    if (gdbFileDescriptor >= 0 && !reentered)
    {
	char textbuf[BUFMAX], hexbuf[2 * BUFMAX], *textscan, *hexscan;

	reentered = true;

	vsnprintf(textbuf, BUFMAX, fmt, args);

	hexscan = hexbuf;
	*hexscan++ = 'O';
	for (textscan = textbuf; *textscan; textscan++)
	    hexscan = byteToHex(*textscan, hexscan);
	*hexscan = '\0';
	putpacket(hexbuf);

	reentered = false;
    }
}
