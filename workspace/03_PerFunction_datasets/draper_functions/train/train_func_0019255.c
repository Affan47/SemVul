get_ftext(FILE *ffile)


{
	char	command[BUFSIZ];
	char	c;

	ftext[0] = 0;

	while(!feof(ffile))
	{
		c = fgetc(ffile);
		switch(c)
		{
		case '%':

			strcpy(command,read_word(ffile));
			if(isequal(command,"end"))
				return(NULL);
			if(isequal(command,"line"))
			{
				strcat(ftext,"   ");
				return(ftext);
			}
			break;

		case '\\':
			c = fgetc(ffile);
			translate_escape(ftext,c);
			break;

		case '\n':
			return(ftext);
			break;

		default:
			sprintf(ftext,"%s%c",ftext,c);
			break;
		}
	}
	return NULL;
}
