v7_dhcp_address() {
	ANTLR_USE_NAMESPACE(antlr)RefToken  dhcp = ANTLR_USE_NAMESPACE(antlr)nullToken;

	try {
		dhcp = LT(1);
		match(DHCP);
		if ( inputState->guessing==0 ) {
#line 1689 "pix.g"

			std::string addr = dhcp->getText();
			importer->addInterfaceAddress(addr, "");
			*dbg << LT(1)->getLine() << ":"
			<< " INTRFACE ADDRESS: " << addr << std::endl;
			consumeUntil(NEWLINE);

#line 6500 "PIXCfgParser.cpp"
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
