get_option_pos(char *line)
{
    long i=0;


    if( line!=NULL && strlen(line) > 0 )
    {
	for(i=0; line[i]!='\0'; i++)
	{
	    if( line[i]==' ' )
	    {
		i++;
	        break;
	    }
	}
    }


    if( line!=NULL && strlen(line) > 0 )
    {
	for(i=i; line[i]!='\0'; i++)
	{
	    if( line[i]!=' ' )
	      break;
	}
    }

    return i;
}
