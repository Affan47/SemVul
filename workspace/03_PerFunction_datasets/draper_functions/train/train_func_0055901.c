DBFReadIntegerAttribute( DBFHandle psDBF, int iRecord, int iField )

{
    double	*pdValue;

    pdValue = (double *) DBFReadAttribute( psDBF, iRecord, iField, 'N' );

    if( pdValue == NULL )
        return 0;
    else
        return( (int) *pdValue );
}
