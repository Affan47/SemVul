bio_seek(bio_file_t *bio, int offset, int whence)
{
	switch(whence)
	{
	  case SEEK_SET:
		bio->pos = offset;
		break;
	  case SEEK_CUR:
		bio->pos += offset;
		break;
	  case SEEK_END:
		bio->pos = bio->len - offset;
		break;
	}
	if(bio->pos < 0)
		bio->pos = 0;
	else if(bio->pos > bio->len)
		bio->pos = bio->len;
	return 0;
}
