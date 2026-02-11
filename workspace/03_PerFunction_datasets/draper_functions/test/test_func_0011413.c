x(RefFMTNode _t) {
	RefFMTNode x_AST_in = (_t == RefFMTNode(ASTNULL)) ? RefFMTNode(antlr::nullAST) : _t;
	RefFMTNode tl = RefFMTNode(antlr::nullAST);

	tl = _t;
	match(antlr::RefAST(_t),X);
	_t = _t->getNextSibling();

	if( _t != static_cast<RefFMTNode>(antlr::nullAST))
	{
	int    tlVal = tl->getW();
	ioss.seekg( tlVal, std::ios_base::cur);
	}

	_retTree = _t;
}
