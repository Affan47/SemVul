RasterizeLayer( GDALDatasetShadow *dataset,
                 int bands, int *band_list,
                 OGRLayerShadow *layer,
                 void *pfnTransformer = NULL,
                 void *pTransformArg = NULL,
		 int burn_values = 0, double *burn_values_list = NULL,
                 char **options = NULL,
                 GDALProgressFunc callback=NULL,
                 void* callback_data=NULL) {

    CPLErr eErr;

    CPLErrorReset();

    if( burn_values == 0 )
    {
        burn_values_list = (double *) CPLMalloc(sizeof(double)*bands);
        for( int i = 0; i < bands; i++ )
            burn_values_list[i] = 255.0;
    }
    else if( burn_values != bands )
    {
        CPLError( CE_Failure, CPLE_AppDefined,
                  "Did not get the expected number of burn values in RasterizeLayer()" );
        return CE_Failure;
    }

    eErr = GDALRasterizeLayers( dataset, bands, band_list,
                                1, &layer,
                                (GDALTransformerFunc) pfnTransformer,
                                pTransformArg,
                                burn_values_list, options,
                                callback, callback_data );

    if( burn_values == 0 )
        CPLFree( burn_values_list );

    return eErr;
}
