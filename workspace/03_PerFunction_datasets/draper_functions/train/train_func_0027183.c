split( char *inString, char *inSeparator, int *outNumParts ) {
    SimpleVector<char *> *parts = new SimpleVector<char *>();

    char *workingString = stringDuplicate( inString );
    char *workingStart = workingString;

    int separatorLength = strlen( inSeparator );

    char *foundSeparator = strstr( workingString, inSeparator );

    while( foundSeparator != NULL ) {

        foundSeparator[0] = '\0';
        parts->push_back( stringDuplicate( workingString ) );


        workingString = &( foundSeparator[ separatorLength ] );
        foundSeparator = strstr( workingString, inSeparator );
        }


    parts->push_back( stringDuplicate( workingString ) );


    delete [] workingStart;

    *outNumParts = parts->size();
    char **returnArray = parts->getElementArray();

    delete parts;

    return returnArray;
    }
