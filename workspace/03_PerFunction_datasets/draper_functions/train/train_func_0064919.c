m_length() {

	try {
		match(M_LENGTH);
		if ( inputState->guessing==0 ) {
#line 838 "iptables.g"

			*dbg << " LENGTH";

#line 2280 "IPTCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_5);
		} else {
			throw;
		}
	}
}
