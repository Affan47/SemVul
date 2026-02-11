ReadSTX()
{
    CPLString osPath = CPLGetPath( GetDescription() );
    CPLString osName = CPLGetBasename( GetDescription() );
    CPLString osSTXFilename = CPLFormCIFilename( osPath, osName, "stx" );


    VSILFILE	*fp;
    if ((fp = VSIFOpenL( osSTXFilename, "rt" )) != NULL)
    {
      const char *	pszLine;
      while( (pszLine = CPLReadLineL( fp )) != NULL )
      {
          char	**papszTokens;
          papszTokens = CSLTokenizeStringComplex( pszLine, " \t", TRUE, FALSE );
          int nTokens = CSLCount( papszTokens );
          if( nTokens >= 5 )
          {
            int i = atoi(papszTokens[0]);
            if (i > 0 && i <= nBands)
            {
              EHdrRasterBand* poBand = (EHdrRasterBand*)papoBands[i-1];
              poBand->dfMin = atof(papszTokens[1]);
              poBand->dfMax = atof(papszTokens[2]);

              int bNoDataSet = FALSE;
              double dfNoData = poBand->GetNoDataValue(&bNoDataSet);
              if (bNoDataSet && dfNoData == poBand->dfMin)
              {

                  CPLDebug("EHDr", "Ignoring .stx file where min == nodata. "
                           "The nodata value shouldn't be taken into account "
                           "in minimum value computation.");
                  CSLDestroy( papszTokens );
                  papszTokens = NULL;
                  break;
              }

              poBand->minmaxmeanstddev = HAS_MIN_FLAG | HAS_MAX_FLAG;

              if ( !EQUAL(papszTokens[3], "#") )
              {
                poBand->dfMean   = atof(papszTokens[3]);
                poBand->minmaxmeanstddev |= HAS_MEAN_FLAG;
              }
              if ( !EQUAL(papszTokens[4], "#") )
              {
                poBand->dfStdDev = atof(papszTokens[4]);
                poBand->minmaxmeanstddev |= HAS_STDDEV_FLAG;
              }

              if( nTokens >= 6 && !EQUAL(papszTokens[5], "#") )
                poBand->SetMetadataItem( "STRETCHMIN", papszTokens[5], "RENDERING_HINTS" );

              if( nTokens >= 7 && !EQUAL(papszTokens[6], "#") )
                poBand->SetMetadataItem( "STRETCHMAX", papszTokens[6], "RENDERING_HINTS" );
            }
          }

          CSLDestroy( papszTokens );
      }

      VSIFCloseL( fp );
    }

    return CE_None;
}
