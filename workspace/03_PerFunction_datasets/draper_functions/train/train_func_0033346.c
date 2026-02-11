_perl_xmmsclient_call_xs (pTHX_ void (*subaddr) (pTHX_ CV *), CV *cv, SV **mark) {
	dSP;
	PUSHMARK (mark);
	(*subaddr) (aTHX_ cv);
	PUTBACK;
}
