gdbstub_state_new ( struct gdbstub *stub, char ch ) {
	if ( ch == '$' ) {
		stub->len = 0;
		stub->parse = gdbstub_state_data;
	}
}
