pair_of_ports_spec() {

	try {
		if ( inputState->guessing==0 ) {
#line 1195 "pix.g"

			importer->tmp_port_spec_2 = "";

#line 5648 "PIXCfgParser.cpp"
		}
		tcp_udp_port_spec();
		if ( inputState->guessing==0 ) {
#line 1199 "pix.g"

			importer->tmp_port_spec += importer->tmp_port_spec_2;

#line 5656 "PIXCfgParser.cpp"
		}
		tcp_udp_port_spec();
		if ( inputState->guessing==0 ) {
#line 1203 "pix.g"

			importer->tmp_port_spec += " ";
			importer->tmp_port_spec += importer->tmp_port_spec_2;

#line 5665 "PIXCfgParser.cpp"
		}
	}
	catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& ex) {
		if( inputState->guessing == 0 ) {
			reportError(ex);
			recover(ex,_tokenSet_15);
		} else {
			throw;
		}
	}
}
