httpRequestFailed(memBuf_t *mp)
{
	freeMembuf(mp);
	log(("%s", curl_easy_strerror(curlrc)));
	log(("%s", globalErrorbuf));
	return NULL;
}
