getSetting( char *inSettingName ) {

    char *fileName = getSettingsFileName( inSettingName );
    File *settingsFile = new File( NULL, fileName );

    delete [] fileName;

    char *fileContents = settingsFile->readFileContents();

    delete settingsFile;


    if( fileContents == NULL ) {

        return new SimpleVector<char *>();
        }


    SimpleVector<char *> *returnVector = tokenizeString( fileContents );

    delete [] fileContents;

    return returnVector;
    }
