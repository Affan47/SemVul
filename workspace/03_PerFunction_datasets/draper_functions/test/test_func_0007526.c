gl_read_gaussn_file_geomi(gchar *FileName,gint num)
{


	FILE* fd;
 	if ((!FileName) || (strcmp(FileName,"") == 0))
 	{
		Message(_("Sorry\n No file selected"),_("Error"),TRUE);
    		return FALSE;
 	}
 	fd = FOpen(FileName, "rb");
 	if(fd ==NULL)
 	{
  		Message(_("Sorry\nI can not open this file"),_("Error"),TRUE);
  		return FALSE;
 	}
	fclose(fd);


	if(gl_read_gaussn_file_geomi_str(FileName,num,"Standard orientation:"))
		return TRUE;
	if(gl_read_gaussn_file_geomi_str(FileName,num,"Input orientation:"))
		return TRUE;

	if(!gl_read_gaussn_file_geomi_str(FileName,num,"Z-Matrix orientation:"))
	{
  		Message(_("Sorry\nI can not read geometry in this file"),_("Error"),TRUE);
		return FALSE;
	}
	return TRUE;

}
