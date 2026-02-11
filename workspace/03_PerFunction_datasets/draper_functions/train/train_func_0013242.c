get_num_density(FILE* file, gchar* buffer, gint len)
{
	gint numOfGrid = 0;
	while(!feof(file))
	{
		if(!fgets(buffer,len,file))
			return 0;
		if(strstr(buffer,"GridName="))
		{
			numOfGrid++;
			if(strstr(buffer,"Density"))
				return numOfGrid;
		}
	}
	return 0;
}
