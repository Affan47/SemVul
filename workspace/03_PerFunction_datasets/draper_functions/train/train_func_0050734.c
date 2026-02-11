copyfile(char* source, char * destination, int overwrite, int mode)
{
#if defined _WIN32
	return (0 == CopyFile(source,destination,overwrite ? FALSE : TRUE));
#else
#ifdef DB_USE_64LFS
#define OPEN_FUNCTION dblayer_open_large
#else
#define OPEN_FUNCTION open
#endif
	int source_fd = -1;
	int dest_fd = -1;
	char *buffer = NULL;
	int return_value = -1;
	int bytes_to_write = 0;


	buffer =  slapi_ch_malloc(64*1024);
	if (NULL == buffer)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name, "copy file: memory allocation failed\n");
		goto error;
	}

	source_fd = OPEN_FUNCTION(source,O_RDONLY,0);
	if (-1 == source_fd)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"copyfile: failed to open source file %s\n", source);
		goto error;
	}

	dest_fd = OPEN_FUNCTION(destination,O_CREAT | O_WRONLY, mode);
	if (-1 == dest_fd)
	{
		slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"copyfile: failed to open destination file %s\n", destination);
		goto error;
	}

	while (1)
	{
		return_value = read(source_fd,buffer,64*1024);
		if (return_value <= 0)
		{

			break;
		}
		bytes_to_write = return_value;
		return_value = write(dest_fd,buffer,bytes_to_write);
		if (return_value != bytes_to_write)
		{

			slapi_log_error(SLAPI_LOG_FATAL, repl_plugin_name,
						"copyfile: failed to write to destination file %s\n", destination);
			return_value = -1;
			break;
		}
	}
error:
	if (source_fd != -1)
	{
		close(source_fd);
	}
	if (dest_fd != -1)
	{
		close(dest_fd);
	}
	slapi_ch_free_string(&buffer);
	return return_value;
#endif
}
