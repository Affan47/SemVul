GB_CopyFile(const char *src, const char *dst)
{
	CATCH_ERROR
	{
		FILE_copy(src, dst);
	}
	END_CATCH_ERROR
}
