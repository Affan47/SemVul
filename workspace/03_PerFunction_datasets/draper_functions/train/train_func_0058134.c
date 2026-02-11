finish()
{
	if (!finished_)
	{
		finished_ = true;
		if (deflateEnd(&z_) != Z_OK)
		{
			return ATC_ERR_ZLIB_ERROR;
		}
	}

	return ATC_OK;
}
