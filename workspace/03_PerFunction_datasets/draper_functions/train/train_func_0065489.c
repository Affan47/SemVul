buffered_fullread(mpg123_handle *fr, unsigned char *out, ssize_t count)
{
	struct bufferchain *bc = &fr->rdat.buffer;
	ssize_t gotcount;
	if(bc->size - bc->pos < count)
	{
		unsigned char readbuf[BUFFBLOCK];
		ssize_t need = count - (bc->size-bc->pos);
		while(need>0)
		{
			int ret;
			ssize_t got = fr->rdat.fullread(fr, readbuf, BUFFBLOCK);
			if(got < 0)
			{
				if(NOQUIET) error("buffer reading");
				return READER_ERROR;
			}

			if(VERBOSE3) debug1("buffered_fullread: buffering %li bytes from stream (if > 0)", (long)got);
			if(got > 0 && (ret=bc_add(bc, readbuf, got)) != 0)
			{
				if(NOQUIET) error1("unable to add to chain, return: %i", ret);
				return READER_ERROR;
			}

			need -= got;
			if(got < BUFFBLOCK)
			{
				if(VERBOSE3) fprintf(stderr, "Note: Input data end.\n");
				break;
			}
		}
		if(bc->size - bc->pos < count)
		count = bc->size - bc->pos;
	}
	gotcount = bc_give(bc, out, count);

	if(VERBOSE3) debug2("wanted %li, got %li", (long)count, (long)gotcount);

	if(gotcount != count){ if(NOQUIET) error("gotcount != count"); return READER_ERROR; }
	else return gotcount;
}
