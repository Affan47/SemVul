user_exists(G_CONST_RETURN gchar *username)
{

    FILE *fp;
    long conf_size;
    int x, user_exists = 0;
    char tempname[4096]="";
    char *check_buffer;


    if((fp=fopen(GP_PASSWD_BUF,"r"))==NULL)
    {

    }
    else
      {
	    fseek(fp, 0, SEEK_END);
	    conf_size = ftell(fp);
	    rewind(fp);

	    check_buffer = allocate(conf_size);

	    if( conf_size > 1 )
	    while(fgets(check_buffer, conf_size, fp)!=NULL)
	    {
		for(x=0; check_buffer[x]; x++)
		{
		    if(check_buffer[x]==':')
		    {
			sprintf(tempname, "%s", check_buffer);
			tempname[x]='\0';
			if( strcmp(username, tempname) == 0 )
			{
			    user_exists = 1;
			    break;
			}
		    }
		    if( check_buffer[x]=='\0' || check_buffer[x]=='\n' )
		    break;
		}
	    }
	    free(check_buffer);
      }

    fclose(fp);


    if((fp=fopen(GP_SHADOW_BUF,"r"))==NULL)
    {

    }
    else
      {
	    fseek(fp, 0, SEEK_END);
	    conf_size = ftell(fp);
	    rewind(fp);

	    check_buffer = allocate(conf_size);

	    if( conf_size > 1 )
	    while(fgets(check_buffer, conf_size, fp)!=NULL)
	    {
		for(x=0; check_buffer[x]; x++)
		{
		    if(check_buffer[x]==':')
		    {
			sprintf(tempname, "%s", check_buffer);
			tempname[x]='\0';
			if( strstr(username, tempname)
			&& strlen(username) == strlen(tempname) )
			{
			    user_exists = 1;
			    break;
			}
		    }
		    if( check_buffer[x]=='\0' || check_buffer[x]=='\n' )
		    break;
		}
	    }
	    free(check_buffer);
	    fclose(fp);
      }

    return user_exists;
}
