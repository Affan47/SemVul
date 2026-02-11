CL_HTTP_Recv (void *ptr, size_t size, size_t nmemb, void *stream)
{
	size_t		bytes;
	dlhandle_t	*dl;

	dl = (dlhandle_t *)stream;

	bytes = size * nmemb;

	if (!dl->fileSize)
	{
		dl->fileSize = bytes > 131072 ? bytes : 131072;
		dl->tempBuffer = Z_TagMalloc ((int)dl->fileSize, TAG_CL_DOWNLOAD);
	}
	else if (dl->position + bytes >= dl->fileSize - 1)
	{
		char		*tmp;

		tmp = dl->tempBuffer;

		dl->tempBuffer = Z_TagMalloc ((int)(dl->fileSize*2), TAG_CL_DOWNLOAD);
		memcpy (dl->tempBuffer, tmp, dl->fileSize);
		Z_Free (tmp);
		dl->fileSize *= 2;
	}

	memcpy (dl->tempBuffer + dl->position, ptr, bytes);
	dl->position += bytes;
	dl->tempBuffer[dl->position] = 0;

	return bytes;
}
