SaveFile( const char* filename, bool compact )
{
    FILE* fp = callfopen( filename, "w" );
    if ( !fp ) {
        SetError( XML_ERROR_FILE_COULD_NOT_BE_OPENED, filename, 0 );
        return _errorID;
    }
    SaveFile(fp, compact);
    fclose( fp );
    return _errorID;
}
