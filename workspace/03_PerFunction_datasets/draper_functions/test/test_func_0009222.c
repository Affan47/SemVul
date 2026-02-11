parseConfigFile(char* filename)
{
    FILE*   fp;
    char    key[MAX_KEY_LEN];
    char    keyvalue[MAX_VALUE_LEN];
    int     r;

    if ( (fp = fopen( filename, "r" )) != NULL )
    {
        while ( !feof(fp) )
        {
            r = getKey(fp, key);
            if ( r == -1 )
                break;
            else if ( r == 1 )
                continue;

            if ( getValue(fp, keyvalue) == -1 )
                break;

            if ( setConfig( key, keyvalue, 0 ) != 0 )
            {
                uError("db: put: %s", strerror(errno));
                bailout();
            }
        }

        fclose(fp);
    }
}
