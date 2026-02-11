find_maximum_descendent_count( const std::string& s )
{
    int result = 0;

    std::vector<int> adjacenciesAtLevel( s.size(), 0 );
    int currentLevel = 0;
    for( std::string::size_type i=1; i < s.size(); ++i ){

        int d = s[i] - '0';

        if( d > 0 ){

            adjacenciesAtLevel[d-1]++;
            if( adjacenciesAtLevel[d-1] > result )
                result = adjacenciesAtLevel[d-1];

        }

        if( d < currentLevel ){
            for( std::vector<int>::iterator j = adjacenciesAtLevel.begin() + d;
                    j != adjacenciesAtLevel.begin() + currentLevel; ++j ){

                *j = 0;
            }
        }

        currentLevel = d;
    }

    return result;
}
