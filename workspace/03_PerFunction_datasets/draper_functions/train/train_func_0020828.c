EM_reset( const char * fname, FILE * fd )
{
    anyErrors = FALSE;
    fileName = fname ? fname : (c_str)"";
    lineNum = 1;
    EM_lineNum = 1;


    IntList curr = NULL;
    while( linePos )
    {
        curr = linePos;
        linePos = linePos->rest;

        free( curr );
    }


    linePos = intList( 0, NULL );

    return TRUE;
}
