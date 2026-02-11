letter_sed( WORD_ID aIdx, WORD_ID bIdx )
{

	pair< WORD_ID, WORD_ID > pIdx = make_pair( aIdx, bIdx );
	unsigned int value;
	bool ret = GetLSEDCache(pIdx, value);
	if (ret) {
		return value;
	}


	const string &a = GetVocabulary().GetWord( aIdx );
	const string &b = GetVocabulary().GetWord( bIdx );


	unsigned int **cost  = (unsigned int**) calloc( sizeof( unsigned int*  ), a.size()+1 );
	for( unsigned int i=0; i<=a.size(); i++ ) {
		cost[i] = (unsigned int*) calloc( sizeof(unsigned int), b.size()+1 );
		cost[i][0] = i;
	}
	for( unsigned int j=0; j<=b.size(); j++ ) {
		cost[0][j] = j;
	}


	for( unsigned int i=1; i<=a.size(); i++ ) {
		for( unsigned int j=1; j<=b.size(); j++ ) {

			unsigned int ins = cost[i-1][j] + 1;
			unsigned int del = cost[i][j-1] + 1;
			bool match = (a.substr(i-1,1).compare( b.substr(j-1,1) ) == 0);
			unsigned int diag = cost[i-1][j-1] + (match ? 0 : 1);

			unsigned int min = (ins < del) ? ins : del;
			min = (diag < min) ? diag : min;

			cost[i][j] = min;
		}
	}


	unsigned int final = cost[a.size()][b.size()];
	for( unsigned int i=0; i<=a.size(); i++ ) {
		free( cost[i] );
	}
	free( cost );


	SetLSEDCache(pIdx, final);
	return final;
}
