save ( void )
{

	CGraph.save();


	TODO.save();


	++tryLevel;
	Manager.ensureLevel(getCurLevel());


	clearBC();

	incStat(nStateSaves);

	if ( LLM.isWritable(llSRState) )
		LL << " ss(" << getCurLevel()-1 << ")";
#ifdef __DEBUG_SAVE_RESTORE
	writeRoot(llSRState);
#endif
}
