no_commands() {

	try {
		match(NO);
		if ( inputState->guessing==0 ) {
#line 858 "pix.g"

			*dbg << " TOP LEVEL \"NO\" COMMAND: "
			<< LT(0)->getText() << std::endl;
			consumeUntil(NEWLINE);

#line 1872 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_1);
		} else {
			throw;
		}
	}
}
