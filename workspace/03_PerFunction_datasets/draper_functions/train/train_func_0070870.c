traceOut(const char* rname)
{
	for( int i = 0; i < traceDepth; i++ )
		ANTLR_USE_NAMESPACE(std)cout << " ";

	ANTLR_USE_NAMESPACE(std)cout << "< " << rname
		<< "; LA(1)==" << LT(1)->getText().c_str()
		<<	((inputState->guessing>0)?" [guessing]":"")
		<< ANTLR_USE_NAMESPACE(std)endl;

	traceDepth--;
}
