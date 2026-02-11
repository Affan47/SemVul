smbuser_exists(G_CONST_RETURN gchar *username)
{

    FILE *fp;
    char *line;
    long conf_size;
    int x, user_exists = 0;
    char tempname[4096]="";


    get_gadmin_samba_users();


    if((fp=fopen(GADMIN_SAMBA_USERS,"r"))==NULL)
    {

    }
    else
      {
	    fseek(fp, 0, SEEK_END);
	    conf_size = ftell(fp);
	    rewind(fp);
	    line = allocate(conf_size);

	    if( conf_size > 1 )
	    while(fgets(line, conf_size, fp)!=NULL)
	    {
		for(x=0; line[x]; x++)
		{
		    if( line[x]==':' )
		    {
			snprintf(tempname, 4000, "%s", line);
			tempname[x]='\0';
			if( ! strcmp(username, tempname) )
			{
			    user_exists = 1;
			    break;
			}
		    }
		}
		if( user_exists )
		  break;
	    }
	    free(line);
	    fclose(fp);
      }

    return user_exists;
}
