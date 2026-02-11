FS_Read (void *buffer, int len, FILE *f)
{
	int		block, remaining;
	int		read;
	byte	*buf;
	int		tries;

	buf = (byte *)buffer;


	remaining = len;
	tries = 0;
	while (remaining)
	{
		block = remaining;
		if (block > MAX_READ)
			block = MAX_READ;
		read = fread (buf, 1, block, f);
		if (read == 0)
		{
			if ( feof( f ) )
				Com_Error( ERR_FATAL, "FS_Read: premature end-of-file");
			if ( ferror( f ) )
				Com_Error( ERR_FATAL, "FS_Read: file read error");
			Com_Error (ERR_FATAL, "FS_Read: 0 bytes read");
		}
		if (read == -1)
			Com_Error (ERR_FATAL, "FS_Read: -1 bytes read");


		remaining -= read;
		buf += read;
	}
}
