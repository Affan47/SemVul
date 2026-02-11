macro_definition() {

	try {
		match(WORD);
		match(EQUAL);
#line 184 "pf.g"

		importer->clear();
		importer->setCurrentLineNumber(LT(0)->getLine());
		consumeUntil(NEWLINE);

#line 208 "PFCfgParser.cpp"
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		reportError(ex);
		recover(ex,_tokenSet_1);
	}
}
