SplitLine ( char*& pName, char*& pValue )
{
	register char* p = Line;

	while ( *p && isspace (*p) ) ++p;
	pName = p;

	for ( ; *p && *p != '='; ++p ) (void)NULL;
	if (!*p) return 1;


	pValue = p+1;

	for ( *p=0, --p; p!=Line && isspace (*p); --p ) *p=0;
	if ( p == Line && isspace (*p) ) return 2;


	for ( p=pValue; *p && isspace (*p); ++p ) (void)NULL;
	if (!*p) return 3;
	pValue = p;


	for ( p=pValue+strlen(pValue)-1; isspace (*p) && p!=pValue; --p ) *p=0;
	if ( p == pValue && isspace (*p) ) return 4;

	#ifdef USE_DEBUG
		cerr << "\nfound string \'" << pName << "\'=\'" << pValue << "\'";
	#endif

	return 0;
}
