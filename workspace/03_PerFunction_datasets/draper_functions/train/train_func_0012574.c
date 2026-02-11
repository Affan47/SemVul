OpenOutputLog (
    const Char *        filename )
{


    if ( OutputLog != 0 )
        return 0;


    outputLogFile.file = SyFopen( filename, "w" );
    outputLogFile.isstream = 0;
    if ( outputLogFile.file == -1 )
        return 0;

    OutputLog = &outputLogFile;


    return 1;
}
