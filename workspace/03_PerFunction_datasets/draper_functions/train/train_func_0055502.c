id3_to_utf8(mpg123_string *sb, unsigned char encoding, const unsigned char *source, size_t source_size, int noquiet)
{
	unsigned int bwidth;
	debug1("encoding: %u", encoding);


	if(encoding > mpg123_id3_enc_max)
	{
		if(noquiet) error1("Unknown text encoding %u, I take no chances, sorry!", encoding);

		mpg123_free_string(sb);
		return;
	}
	bwidth = encoding_widths[encoding];

	if(encoding != mpg123_id3_utf16be)
	while(source_size > bwidth && source[0] == 0)
	{
		--source_size;
		++source;
		debug("skipped leading zero");
	}
	if(source_size % bwidth)
	{

		if(noquiet) warning2("Weird tag size %d for encoding %u - I will probably trim too early or something but I think the MP3 is broken.", (int)source_size, encoding);
		source_size -= source_size % bwidth;
	}
	text_converters[encoding](sb, source, source_size, noquiet);
}
