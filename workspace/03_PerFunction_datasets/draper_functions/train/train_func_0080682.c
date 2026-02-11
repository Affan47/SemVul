computeLevelForExperience( uint experience )
{
	uint ret;
	uint i;
	uint nbLevels = _levels.count();

	ret = nbLevels;
	if( experience <  ( _levels.at( 0 ) ) ) {
		ret = 0;
	} else {
		for( i = 1; i < nbLevels; i++ ) {
			if( ( experience <  ( _levels.at( i ) ) ) && ( experience >=  ( _levels.at( i-1 ) ) ) )  {
				ret = i;
				break;
			}
		}
	}

	return ret;
}
