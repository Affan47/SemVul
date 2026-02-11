OpenNewFile(char *filename, nffile_t *nffile, int compressed, int anonymized, char *ident) {
size_t			len;
int 			flags;


	if ( nffile == NULL ) {
		nffile = NewFile();
		if ( nffile == NULL ) {
			return NULL;
		}
	}

	flags = compressed ? FLAG_COMPRESSED : 0;
	if ( anonymized )
		SetFlag(flags, FLAG_ANONYMIZED);

	nffile->file_header->flags 	   = flags;

	if ( strcmp(filename, "-") == 0 ) {
		nffile->fd = STDOUT_FILENO;
	} else {
		nffile->fd = open(filename, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH );
		if ( nffile->fd < 0 ) {
			LogError("Failed to open file %s: '%s'" , filename, strerror(errno));
			return NULL;
		}
	}


	if ( nffile->stat_record ) {
		memset((void *)nffile->stat_record, 0, sizeof(stat_record_t));
		nffile->stat_record->first_seen = 0x7fffffff;
		nffile->stat_record->msec_first = 999;
	}

	if ( ident ) {
		strncpy(nffile->file_header->ident, ident, IDENTLEN);
		nffile->file_header->ident[IDENTLEN - 1] = 0;
	}


	if ( TestFlag(flags, FLAG_COMPRESSED) ) {
		if ( !lzo_initialized && !LZO_initialize() ) {
			LogError("Failed to initialize compression");
			close(nffile->fd);
			return NULL;
		}
    	}

	nffile->file_header->NumBlocks = 0;
	len = sizeof(file_header_t);
	if ( write(nffile->fd, (void *)nffile->file_header, len) < len ) {
		LogError("write() error in %s line %d: %s\n", __FILE__, __LINE__, strerror(errno) );
		close(nffile->fd);
		return NULL;
	}


	len = sizeof(stat_record_t);
	if ( write(nffile->fd, (void *)nffile->stat_record, len) < len ) {
		LogError("write() error in %s line %d: %s\n", __FILE__, __LINE__, strerror(errno) );
		close(nffile->fd);
		return NULL;
	}


	return nffile;

}
