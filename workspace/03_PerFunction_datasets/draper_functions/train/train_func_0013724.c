DumpAliases ( XMP_TextOutputProc outProc,
                       void *             refCon )
{
	XMP_Assert ( outProc != 0 );
	XMP_Status status = 0;

	XMP_Assert ( sRegisteredAliasMap != 0 );

	XMP_cAliasMapPos aliasPos;
	XMP_cAliasMapPos aliasEnd = sRegisteredAliasMap->end();

	size_t maxLen = 0;
	for ( aliasPos = sRegisteredAliasMap->begin(); aliasPos != aliasEnd; ++aliasPos ) {
		size_t currLen = aliasPos->first.size();
		if ( currLen > maxLen ) maxLen = currLen;
	}

	OutProcLiteral ( "Dumping alias name to actual path map" );
	OutProcNewline();

	for ( aliasPos = sRegisteredAliasMap->begin(); aliasPos != aliasEnd; ++aliasPos ) {

		OutProcNChars ( "   ", 3 );
		DumpClearString ( aliasPos->first, outProc, refCon );
		OutProcPadding ( maxLen - aliasPos->first.size() );
		OutProcNChars ( " => ", 4 );

		size_t actualPathSize = aliasPos->second.size();
		for ( size_t stepNum = 1; stepNum < actualPathSize; ++stepNum ) OutProcString ( aliasPos->second[stepNum].step );

		XMP_OptionBits arrayForm = aliasPos->second[1].options & kXMP_PropArrayFormMask;

		if ( arrayForm == 0 ) {
			if ( actualPathSize != 2 ) OutProcLiteral ( "  ** bad actual path **" );
		} else {
			OutProcNChars ( "  ", 2 );
			DumpNodeOptions ( arrayForm, outProc, refCon );
			if ( ! (arrayForm & kXMP_PropValueIsArray) ) OutProcLiteral ( "  ** bad array form **" );
			if ( actualPathSize != 3 ) OutProcLiteral ( "  ** bad actual path **" );
		}

		if ( aliasPos->second[0].options != kXMP_SchemaNode ) OutProcLiteral ( "  ** bad schema form **" );

		OutProcNewline();

	}

EXIT:
	return status;

}
