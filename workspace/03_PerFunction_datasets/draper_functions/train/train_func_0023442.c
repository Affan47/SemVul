open(ostream *dst, const char key[ATC_KEY_SIZE])
{

	string header;
	generatePlainHeader(&header);

	dst->write(header.data(), header.size());

	rijndael_.MakeKey(key, CRijndael::sm_chain0, ATC_KEY_SIZE, ATC_BUF_SIZE);

	if (dst->good())
	{
		return ATC_OK;
	} else {
		return ATC_ERR_OSTREAM_FAILURE;
	}
}
