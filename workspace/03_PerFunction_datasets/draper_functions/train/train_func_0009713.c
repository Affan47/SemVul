concatonate( const char *inStringA, const char *inStringB ) {
    char **tempArray = new char*[2];
    tempArray[ 0 ] = (char *)inStringA;
    tempArray[ 1 ] = (char *)inStringB;

    char *result = join( tempArray, 2, "" );

    delete [] tempArray;

    return result;
    }
