bz2_decompress(char* dest, size_t* destlen,
	       const char* _src, size_t srclen)
{

	int ret;
	char* src;
        unsigned int tmpdestlen;

	memcpy(&src, &_src, sizeof(char*));

        tmpdestlen = *destlen;
	ret = BZ2_bzBuffToBuffDecompress(dest, &tmpdestlen, src, srclen, 1, 0);
	if (ret != BZ_OK){
		cl_log(LOG_ERR, "%s: decompression failed",
		       __FUNCTION__);
		return HA_FAIL;
	}

        *destlen = tmpdestlen;

	return HA_OK;
}
