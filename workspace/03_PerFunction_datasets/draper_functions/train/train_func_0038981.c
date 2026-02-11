port_range() {

	try {
		match(RANGE);
		pair_of_ports_spec();
		if ( inputState->guessing==0 ) {
#line 1188 "pix.g"

			importer->tmp_port_op = "range";
			*dbg << "range " << importer->tmp_port_spec;

#line 5548 "PIXCfgParser.cpp"
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
