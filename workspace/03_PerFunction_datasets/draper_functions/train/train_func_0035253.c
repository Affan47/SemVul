ReadHeaderSection()

{
    char szLineBuf[257];
    int  nCode;

    while( (nCode = ReadValue( szLineBuf, sizeof(szLineBuf) )) > -1
           && !EQUAL(szLineBuf,"ENDSEC") )
    {
        if( nCode != 9 )
            continue;

        CPLString osName = szLineBuf;

        ReadValue( szLineBuf, sizeof(szLineBuf) );

        CPLString osValue = szLineBuf;

        oHeaderVariables[osName] = osValue;
    }

    if (nCode != -1)
    {
        nCode = ReadValue( szLineBuf, sizeof(szLineBuf) );
        UnreadValue();
    }


    if (nCode == 9 && EQUALN(szLineBuf,"$", 1) )
    {
        while( (nCode = ReadValue( szLineBuf, sizeof(szLineBuf) )) > -1
            && !EQUAL(szLineBuf,"ENDSEC") )
        {
            if( nCode != 9 )
                continue;

            CPLString osName = szLineBuf;

            ReadValue( szLineBuf, sizeof(szLineBuf) );

            CPLString osValue = szLineBuf;

            oHeaderVariables[osName] = osValue;
        }
    }

    CPLDebug( "DXF", "Read %d header variables.",
              (int) oHeaderVariables.size() );


    CPLString osCodepage = GetVariable( "$DWGCODEPAGE", "ANSI_1252" );


    if( osCodepage == "ANSI_1252" )
        osEncoding = CPL_ENC_ISO8859_1;
    else if( EQUALN(osCodepage,"ANSI_",5) )
    {
        osEncoding = "CP";
        osEncoding += osCodepage + 5;
    }
    else
    {

        osEncoding = CPL_ENC_ISO8859_1;
    }

    if( CPLGetConfigOption( "DXF_ENCODING", NULL ) != NULL )
        osEncoding = CPLGetConfigOption( "DXF_ENCODING", NULL );

    if( osEncoding != CPL_ENC_ISO8859_1 )
        CPLDebug( "DXF", "Treating DXF as encoding '%s', $DWGCODEPAGE='%s'",
                  osEncoding.c_str(), osCodepage.c_str() );
}
