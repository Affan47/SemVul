ParseChildren( VSILFILE * fp )

{
    while( TRUE )
    {
        size_t iOff;
        CPLString osLine;


        if( !ReadLine( fp, osLine ) )
            return FALSE;


        if( (iOff = osLine.find_first_of( '=' )) != std::string::npos )
        {
            CPLString osName = osLine.substr(0,iOff-1);
            osName.Trim();

            CPLString osValue = osLine.c_str() + iOff + 1;
            osValue.Trim();

            MakeSpace();
            papszItemName[nItemCount] = CPLStrdup(osName);
            papszItemValue[nItemCount] = CPLStrdup(osValue);
            papoItemChild[nItemCount] = NULL;

            nItemCount++;
        }


        else if( (iOff = osLine.ifind( " Begin" )) != std::string::npos )
        {
            CPLString osName = osLine.substr(0,iOff);
            osName.Trim();

            MakeSpace();
            papszItemName[nItemCount] = CPLStrdup(osName);
            papszItemValue[nItemCount] = NULL;
            papoItemChild[nItemCount] = new ERSHdrNode();

            nItemCount++;

            if( !papoItemChild[nItemCount-1]->ParseChildren( fp ) )
                return FALSE;
        }


        else if( osLine.ifind( " End" ) != std::string::npos )
        {
            return TRUE;
        }


        else if( osLine.Trim().length() > 0 )
        {
            CPLError( CE_Failure, CPLE_AppDefined,
                      "Unexpected line parsing .ecw:\n%s",
                      osLine.c_str() );
            return FALSE;
        }
    }
}
