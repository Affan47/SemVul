gf_xml_sax_init(GF_SAXParser *parser, unsigned char *BOM)
{
	u32 offset;
	if (!BOM) {
		parser->unicode_type = 0;
		parser->sax_state = SAX_STATE_ELEMENT;
		return GF_OK;
	}

	if (parser->unicode_type >= 0) return gf_xml_sax_parse(parser, BOM);

	offset = 0;
	if ((BOM[0]==0xFF) && (BOM[1]==0xFE)) {
		if (!BOM[2] && !BOM[3]) return GF_NOT_SUPPORTED;
		parser->unicode_type = 2;
		offset = 2;
	} else if ((BOM[0]==0xFE) && (BOM[1]==0xFF)) {
		if (!BOM[2] && !BOM[3]) return GF_NOT_SUPPORTED;
		parser->unicode_type = 1;
		offset = 2;
	} else if ((BOM[0]==0xEF) && (BOM[1]==0xBB) && (BOM[2]==0xBF)) {

		parser->unicode_type = 0;
		offset = 3;
	} else {
		parser->unicode_type = 0;
		offset = 0;
	}
	parser->sax_state = SAX_STATE_ELEMENT;
	return gf_xml_sax_parse(parser, BOM + offset);
}
