check_top_level_end(end_command,type)
char *end_command;
int type;
{
    if ( gstackp == 0 )
	{
	 printf("\"%s\", line %d: \"%s\" found at top level\n",
	       file_name,
	       line_count,
	       eg_command( end_command, type )) ;
	 ++warn_count;
         return(0);
	}
    else
    	return(1);
}
