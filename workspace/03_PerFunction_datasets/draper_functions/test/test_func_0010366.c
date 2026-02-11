create_vbox_file(char *file, int *compression)
{
	int fdin, fdout, len;
	char string[BUFSIZ];
	char *fileout = NULL;
	vaheader_t header;

	if ((fdin = open(file,O_RDONLY)) == -1)
	{
		print_msg(PRT_ERR, msg1, file, strerror(errno));
		return NULL;
	}

	if (read(fdin,&header,sizeof(vaheader_t)) == sizeof(vaheader_t))
	{
		if (compression != NULL)
			*compression = ntohl(header.compression);

		fileout = strdup("/tmp/isdnrepXXXXXX");
		if( (fdout = mkstemp(fileout)) < 0 )
		{
			print_msg(PRT_ERR, msg1, fileout, strerror(errno));
			close(fdin);
			free(fileout);
			return NULL;
		}

		while((len = read(fdin,string,BUFSIZ)) > 0)
		{
			if (write(fdout,string,len) != len)
			{
				print_msg(PRT_ERR, "isdnrep: can't write to file `%s': %s!\n", fileout, strerror(errno));
				close(fdout);
				close(fdin);
				unlink(fileout);
				free(fileout);
				return NULL;
			}
		}

		close(fdout);

		if (len < 0)
		{
			print_msg(PRT_ERR, "isdnrep: can't read from file `%s': %s!\n", file, strerror(errno));
			close(fdin);
			unlink(fileout);
			free(fileout);
			return NULL;
		}
	}

	close(fdin);
	return fileout;
}
