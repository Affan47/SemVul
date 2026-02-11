polish(GLEPcode& pcode, int *rtype) throw(ParserError) {
	Tokenizer* tokens = getTokens();
	string& expr = tokens->next_multilevel_token();
	int pos = tokens->token_pos_col();

	try {

		m_polish->polish(expr.c_str(), pcode, rtype);
	} catch (ParserError err) {
		err.incColumn(pos-1);
		throw err;
	}
}
