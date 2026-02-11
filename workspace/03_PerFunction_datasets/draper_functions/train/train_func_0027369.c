push_LS(Parse_control& pc, lexical_state new_state) {
	if(pc.ls_sp<MAX_LEXICAL_STATES) {
		pc.ls_stack[pc.ls_sp++]=pc.ls;
		pc.ls=new_state;
	} else
		throw Exception(0, 0,
			"push_LS: ls_stack overflow");
}
