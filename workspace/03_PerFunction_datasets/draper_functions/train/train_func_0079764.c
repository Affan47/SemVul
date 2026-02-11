QueryArray( const string & L) {
    for(unsigned int i=0; i<arrayLabels.size(); i++ )
        if( arrayLabels[i] == L ) return arrayValues[i];

    return vector<string>();
}
