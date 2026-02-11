asmcontrol()
{
#ifdef ASM_BARE
    char treasure;
#endif

    asmmode = TRUE;
    if (expect_statement)
       return;

    if (orig_cppmode)
	outnstr("#asm");
    else
    {
	outnstr("!BCC_ASM");
	dumplocs();
    }
#ifndef ASM_BARE
    cppscan(1);
#else
    while (TRUE)
    {
	skipline();
	skipeol();
	if (eofile)
	{
	    eofin("#asm");
	    break;
	}
	if (SYMOFCHAR(ch) == SPECIALCHAR)
	    specialchar();
	treasure = 0;
	if (SYMOFCHAR(ch) == WHITESPACE)
	    treasure = ch;
	blanks();
	if (ch == '#')
	{
	    if (ctext)
	    {
		register char *lptr;

		comment();
		if (treasure != 0)
		    outbyte(treasure);
		lptr = lineptr;
		while (*lptr++ != EOL)
		    outbyte(ch);
		outnl();
	    }
	    gch1();
	    docontrol();
	    if (!asmmode)
		break;
	}
	else
	{
	    if (treasure != 0)
		outbyte(treasure);
	    while (ch != EOL)
	    {
		outbyte(ch);
		gch1();
	    }
	    outnl();
	}
    }
#endif
    if (orig_cppmode)
	outnstr("#endasm");
    else
	outnstr("!BCC_ENDASM");
}
