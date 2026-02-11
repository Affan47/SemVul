StyleFromStyleURL(
    const StyleMapPtr& stylemap,
    const string styleurl,
    OGRStyleTable * poStyleTable)
{


    char *pszUrl = CPLStrdup ( styleurl.c_str (  ) );
    char *pszStyleMapId = CPLStrdup ( stylemap->get_id().c_str (  ) );


    if ( *pszUrl == '#' && poStyleTable ) {


        const char *pszTest = NULL;
        pszTest = poStyleTable->Find ( pszUrl + 1 );
        if ( pszTest ) {
            poStyleTable->AddStyle(pszStyleMapId, pszTest);
        }
    }


    else if ( strchr(pszUrl, '#') ) {

        const char *pszFetch = CPLGetConfigOption ( "LIBKML_EXTERNAL_STYLE", "no" );
        if ( EQUAL(pszFetch, "yes") ) {


            char *pszUrlTmp = CPLStrdup(pszUrl);
            char *pszPound;
            char *pszRemoteStyleName = NULL;

            if ((pszPound = strchr(pszUrlTmp, '#'))) {
                *pszPound = '\0';
                pszRemoteStyleName = pszPound + 1;
            }


            VSILFILE *fp = NULL;
            if ( (fp = VSIFOpenL( CPLFormFilename( "/vsicurl/",
                                                   pszUrlTmp,
                                                  NULL), "r" ))
                 ||  (fp = VSIFOpenL( pszUrlTmp, "r" )) )
            {
                char szbuf[1025];
                std::string oStyle = "";


                size_t nRead;
                do {
                    nRead = VSIFReadL(szbuf, 1, sizeof(szbuf) - 1, fp);
                    if (nRead == 0)
                        break;


                    szbuf[nRead] = '\0';
                    oStyle.append( szbuf );
                } while (!VSIFEofL(fp));

                VSIFCloseL(fp);


                std::string oKmlErrors;
                ElementPtr poKmlRoot = kmldom::Parse ( oStyle, &oKmlErrors );

                if ( !poKmlRoot ) {
                    CPLError ( CE_Failure, CPLE_OpenFailed,
                               "ERROR Parseing style kml %s :%s",
                               pszUrlTmp, oKmlErrors.c_str (  ) );
                    CPLFree(pszUrlTmp);
                    CPLFree ( pszUrl );
                    CPLFree ( pszStyleMapId );

                    return NULL;
                }


                ContainerPtr poKmlContainer;
                kmldom::KmlFactory* poKmlFactory = kmldom::KmlFactory::GetFactory();
                if ( !( poKmlContainer = MyGetContainerFromRoot ( poKmlFactory, poKmlRoot ) ) ) {
                    CPLFree(pszUrlTmp);
                    CPLFree ( pszUrl );
                    CPLFree ( pszStyleMapId );

                    return NULL;
                }


                ParseStyles ( AsDocument ( poKmlContainer ), &poStyleTable );


                const char *pszTest = NULL;
                pszTest = poStyleTable->Find(pszRemoteStyleName);


                if ( pszTest )
                    poStyleTable->AddStyle(pszStyleMapId, pszTest);

            }
            CPLFree(pszUrlTmp);
        }
    }


    CPLFree ( pszUrl );
    CPLFree ( pszStyleMapId );

    return NULL;
}
