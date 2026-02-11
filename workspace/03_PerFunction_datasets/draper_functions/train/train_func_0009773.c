array_sub() {
	returnAST = RefPortugolAST(ANTLR_USE_NAMESPACE(antlr)nullAST);
	ANTLR_USE_NAMESPACE(antlr)ASTPair currentAST;
	RefPortugolAST array_sub_AST = RefPortugolAST(ANTLR_USE_NAMESPACE(antlr)nullAST);
	ANTLR_USE_NAMESPACE(antlr)RefToken  abre = ANTLR_USE_NAMESPACE(antlr)nullToken;
	RefPortugolAST abre_AST = RefPortugolAST(ANTLR_USE_NAMESPACE(antlr)nullAST);
	RefToken tk;

	try {
		{
		for (;;) {
			if ((LA(1) == T_ABREC)) {
				abre = LT(1);
				if ( inputState->guessing == 0 ) {
					abre_AST = astFactory->create(abre);
				}
				match(T_ABREC);
				if ( inputState->guessing==0 ) {
					tk=abre;
				}
				expr();
				if (inputState->guessing==0) {
					astFactory->addASTChild(currentAST, ANTLR_USE_NAMESPACE(antlr)RefAST(returnAST));
				}
				if ( inputState->guessing==0 ) {
					tk = lastToken;
				}
				match(T_FECHAC);
			}
			else {
				goto _loop30;
			}

		}
		_loop30:;
		}
		array_sub_AST = RefPortugolAST(currentAST.root);
	}
	catch (antlr::MismatchedTokenException e) {
		if (inputState->guessing==0) {

			reportParserError(tk->getLine(), getTokenNames()[e.expecting], "", tk->getText());


			BitSet b;
			b.add(T_ATTR);
			b.add(T_KW_DE);

			b.add(T_SEMICOL);
			b.add(T_FECHAC);
			b.add(T_KW_ENTAO);
			b.add(T_KW_FACA);
			b.add(T_KW_ATE);
			consumeUntil(b);

		} else {
			throw;
		}
	}
	returnAST = array_sub_AST;
}
