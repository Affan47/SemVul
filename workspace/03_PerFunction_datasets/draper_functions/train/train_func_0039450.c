partition_neighbors ( Field object )
{
    Array  neighbors;
    int    i, nRefs, nNbrs, origConnections;
    int    *refs;

    DXASSERTGOTO ( DXGetObjectClass ( (Object) object ) == CLASS_FIELD );


    if ( DXEmptyField ( object ) )
        return object;


    if ( ( ERROR == ( neighbors = DXNeighbors ( object ) ) ) )
        return ( DXGetError() == ERROR_NONE ) ? object : ERROR;

    if ( ! DXQueryOriginalSizes ( object, NULL, &origConnections )
         ||
         ! DXGetArrayInfo ( neighbors, NULL, NULL, NULL, NULL, &nNbrs )
         ||
         ( ERROR == ( refs = DXGetArrayData ( neighbors ) ) ) )
        goto error;


    nRefs = origConnections * nNbrs;

    for ( i = 0;  i < nRefs;  i++, refs++ )
        if ( *refs >= origConnections )
            *refs = -2;

    return object;

    error:
        DXASSERT ( DXGetError() != ERROR_NONE );
        return ERROR;
}
