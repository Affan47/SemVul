save(xml_writer& writer, const char_t* indent, unsigned int flags, xml_encoding encoding) const
	{
		impl::xml_buffered_writer buffered_writer(writer, encoding);

		if ((flags & format_write_bom) && encoding != encoding_latin1)
		{

		#ifdef PUGIXML_WCHAR_MODE
			unsigned int bom = 0xfeff;
			buffered_writer.write(static_cast<wchar_t>(bom));
		#else
			buffered_writer.write('\xef', '\xbb', '\xbf');
		#endif
		}

		if (!(flags & format_no_declaration) && !impl::has_declaration(*this))
		{
			buffered_writer.write(PUGIXML_TEXT("<?xml version=\"1.0\""));
			if (encoding == encoding_latin1) buffered_writer.write(PUGIXML_TEXT(" encoding=\"ISO-8859-1\""));
			buffered_writer.write('?', '>');
			if (!(flags & format_raw)) buffered_writer.write('\n');
		}

		impl::node_output(buffered_writer, *this, indent, flags, 0);
	}
