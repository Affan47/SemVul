transcode(const String& src,
	const Charset& source_transcoder,
	const Charset& dest_transcoder) {
	if(src.is_empty())
		return *new String();

	return *new String(transcode((String::Body)src, source_transcoder, dest_transcoder), String::L_CLEAN);
}
