polishPos(const char* fct, int pos, StringIntHash* vars) throw(ParserError) {
	GLEPolish* polish = get_global_polish();
	if (polish != NULL) {
		try {
			int rtype = 1;
			polish->setExprVars(vars);
			polish->polish(fct, m_Pcode, &rtype);
			polish->setExprVars(NULL);
		} catch (ParserError err) {
			err.incColumn(pos-1);
			throw err;
		}
	}
}
