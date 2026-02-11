setoffsets(struct client_config *cconf, FILE *stream, mp3entry *entry)
{
	long start;
	long end;

	if(cconf->startpos > 0 && cconf->startpos < entry->filesize)
		start = cconf->startpos;
	else if(!MODE_ISSET(MODE_SINGLE) && entry->id3v2len)
		start = entry->id3v2len;
	else
		start = 0;
	fseek(stream, start, SEEK_SET);

	if(cconf->endpos > 0 && cconf->endpos < entry->filesize)
		end = cconf->endpos;
	else if(HASID3V1(entry) && end > entry->id3v1len)
		end = entry->filesize - entry->id3v1len;
	else
		end = entry->filesize;

	debug(4, "Start offset is %li, end offset is %li\n", start, end);
	return end;
}
