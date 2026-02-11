SetDefaultHistogram( double dfMin, double dfMax,
                                           int nBuckets, int *panHistogram)

{
    CPLXMLNode *psNode;


    psNode = PamFindMatchingHistogram( psSavedHistograms,
                                       dfMin, dfMax, nBuckets,
                                       TRUE, TRUE );
    if( psNode != NULL )
    {

        CPLRemoveXMLChild( psSavedHistograms, psNode );
        CPLDestroyXMLNode( psNode );
    }


    CPLXMLNode *psHistItem;

    psHistItem = PamHistogramToXMLTree( dfMin, dfMax, nBuckets,
                                        panHistogram, TRUE, FALSE );
    if( psHistItem == NULL )
        return CE_Failure;


    if( psSavedHistograms == NULL )
        psSavedHistograms = CPLCreateXMLNode( NULL, CXT_Element,
                                              "Histograms" );

    psHistItem->psNext = psSavedHistograms->psChild;
    psSavedHistograms->psChild = psHistItem;

    return CE_None;
}
