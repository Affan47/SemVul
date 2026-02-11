new_bmp(gchar* dirname, int i)
{
	gchar* fileName = g_strdup_printf("%s%sgab%d.bmp",dirname,G_DIR_SEPARATOR_S,i);
	gchar* message;
	if(i==1)
	{
		gint j;
		for(j=0;j<100;j++)
		{
			gchar* filestoDelete = g_strdup_printf("%s%sgab%d.bmp",dirname,G_DIR_SEPARATOR_S,j);
			unlink(filestoDelete);
			g_free(filestoDelete);

		}
	}

	message = save_bmp(fileName);
	g_free(fileName);
	return message;
}
