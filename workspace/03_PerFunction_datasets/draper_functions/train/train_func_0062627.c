GB_StreamRead(GB_STREAM *stream, void *addr, int len)
{
	CATCH_ERROR_INT
	{
		if (len < 0)
			ret = STREAM_read_max((STREAM *)stream, addr, -len);
		else
		{
			STREAM_read((STREAM *)stream, addr, len);
			ret = STREAM_eff_read;
		}
	}
	END_CATCH_ERROR_INT
}
