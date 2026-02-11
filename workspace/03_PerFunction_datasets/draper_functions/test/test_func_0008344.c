host_addr() {

	try {
		match(HOST);
		single_addr();
		if ( inputState->guessing==0 ) {
#line 313 "pix.g"

			importer->commitNamedAddressObject();

#line 2291 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_9);
		} else {
			throw;
		}
	}
}
