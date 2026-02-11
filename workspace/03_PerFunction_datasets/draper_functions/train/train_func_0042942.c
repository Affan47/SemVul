DumpNamespaces ( XMP_TextOutputProc outProc,
                          void *             refCon )
{
	XMP_Assert ( outProc != 0 );
	XMP_Status status = 0;

	XMP_StringMapPos p2uEnd = sNamespacePrefixToURIMap->end();
	XMP_StringMapPos u2pEnd = sNamespaceURIToPrefixMap->end();

	status = DumpStringMap ( *sNamespacePrefixToURIMap, "Dumping namespace prefix to URI map", outProc, refCon );
	if ( status != 0 ) goto EXIT;

	if ( sNamespacePrefixToURIMap->size() != sNamespaceURIToPrefixMap->size() ) {
		OutProcLiteral ( "** bad namespace map sizes **" );
		XMP_Throw ( "Fatal namespace map problem", kXMPErr_InternalFailure );
	}

	for ( XMP_StringMapPos nsLeft = sNamespacePrefixToURIMap->begin(); nsLeft != p2uEnd; ++nsLeft ) {

		XMP_StringMapPos nsOther = sNamespaceURIToPrefixMap->find ( nsLeft->second );
		if ( (nsOther == u2pEnd) || (nsLeft != sNamespacePrefixToURIMap->find ( nsOther->second )) ) {
			OutProcLiteral ( "  ** bad namespace URI **  " );
			DumpClearString ( nsLeft->second, outProc, refCon );
			goto FAILURE;
		}

		for ( XMP_StringMapPos nsRight = nsLeft; nsRight != p2uEnd; ++nsRight ) {
			if ( nsRight == nsLeft ) continue;
			if ( nsLeft->second == nsRight->second ) {
				OutProcLiteral ( "  ** duplicate namespace URI **  " );
				DumpClearString ( nsLeft->second, outProc, refCon );
				goto FAILURE;
			}
		}

	}

	for ( XMP_StringMapPos nsLeft = sNamespaceURIToPrefixMap->begin(); nsLeft != u2pEnd; ++nsLeft ) {

		XMP_StringMapPos nsOther = sNamespacePrefixToURIMap->find ( nsLeft->second );
		if ( (nsOther == p2uEnd) || (nsLeft != sNamespaceURIToPrefixMap->find ( nsOther->second )) ) {
			OutProcLiteral ( "  ** bad namespace prefix **  " );
			DumpClearString ( nsLeft->second, outProc, refCon );
			goto FAILURE;
		}

		for ( XMP_StringMapPos nsRight = nsLeft; nsRight != u2pEnd; ++nsRight ) {
			if ( nsRight == nsLeft ) continue;
			if ( nsLeft->second == nsRight->second ) {
				OutProcLiteral ( "  ** duplicate namespace prefix **  " );
				DumpClearString ( nsLeft->second, outProc, refCon );
				goto FAILURE;
			}
		}

	}

EXIT:
	return status;

FAILURE:
	OutProcNewline();
	(void) DumpStringMap ( *sNamespaceURIToPrefixMap, "Dumping namespace URI to prefix map", outProc, refCon );
	XMP_Throw ( "Fatal namespace map problem", kXMPErr_InternalFailure );
	return 0;

}
