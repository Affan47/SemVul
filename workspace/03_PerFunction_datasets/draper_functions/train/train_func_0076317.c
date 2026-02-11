outputcar(char c)
{
	char *dummy;
	char **pat;

	if ( !isspace((unsigned char)c) )
	{	if ( lpos>=llen )
		{	outputEOL();
			if ( filter(linebuffer+LMARGIN,"?;_?",&dummy,&dummy))

				position( chars_consumed_by_filter );
			else if ( c==';' )

				position ( LMARGIN );
			else if ( lastoffset >= LMARGIN )
				position(lastoffset);
			else if ( c!=';' )

				for ( pat=outpat; *pat; pat++)
				{	if ( filter( linebuffer+LMARGIN,
						     *pat,
			        	  	     &dummy,&dummy,&dummy) )
					{	position( chars_consumed_by_filter );
						break;
					};
				};
			lastoffset=lpos;
		};
		if ( isprint((unsigned char)c) || !isascii((unsigned char)c) )
			linebuffer[lpos++]=c;
		linebuffer[lpos]=0;
	}
	else if ( c==' ' )
	{	if (lpos<llen)
		{	linebuffer[lpos++]=' ';
			linebuffer[lpos]=0;
		}
		else
			lpos++;
	}
	else if ( c=='\t')
		do
			outputcar(' ');
		while ( (lpos-LMARGIN) % 8 );
}
