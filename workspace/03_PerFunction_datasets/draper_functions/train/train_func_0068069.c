addLangElem(const vector<string>& toks, TokenizerLangElem* elem, unsigned int pos) {
	if (pos >= toks.size()) {
		m_default = elem;
	} else {
		TokenizerLangHashPtr hash = try_add(toks[pos]);
		hash.addLangElem(toks, elem, pos+1);
	}
}
