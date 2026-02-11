get_file_directory(char* directory, const char* file)
{
	char* end;

	strcpy(directory, file);

	end = directory + strlen(directory) - 1;
	while ((end >= directory) && (end != 0))
	{
		if ( (*end == '\\') || (*end == '/') )
		{
			*end = 0;
			break;
		}
		else
		{
			end--;
		}
	}
}
