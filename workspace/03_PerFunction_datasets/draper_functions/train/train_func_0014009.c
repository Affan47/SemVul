modifyEncodings(String e)
{


	e.toLower();
	String o("Accept-Encoding: identity");
#if ZLIB_VERNUM < 0x1210
#warning 'Accept-Encoding: gzip' is disabled
#else
	if (e.contains("gzip")) {
		o += ",gzip";
	}
#endif
	if (e.contains("deflate")) {
		o += ",deflate";
	}

	return o;
}
