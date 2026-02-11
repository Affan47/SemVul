polish(const char* str, GLEPcode& pcode, int *rtype) throw(ParserError) {
	try {
		m_polish->polish(str, pcode, rtype);
	} catch (ParserError err) {
		err.setParserString(str);
		throw err;
	}
}
