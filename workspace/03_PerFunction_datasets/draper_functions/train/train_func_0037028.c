ValidateVertDatum(OGR_SRSNode *poRoot)
{
    if ( !EQUAL(poRoot->GetValue(), "VERT_DATUM") )
        return OGRERR_NONE;

    if (poRoot->GetChildCount() < 2 )
    {
        CPLDebug( "OGRSpatialReference::Validate",
                  "Invalid number of children : %d", poRoot->GetChildCount() );
        return OGRERR_CORRUPT_DATA;
    }

    if (atoi(poRoot->GetChild(1)->GetValue()) == 0)
    {
        CPLDebug( "OGRSpatialReference::Validate",
                  "Invalid value for datum type (%s) : must be a number\n",
                  poRoot->GetChild(1)->GetValue());
        return OGRERR_CORRUPT_DATA;
    }

    OGR_SRSNode     *poNode;
    int             i;

    for( i = 2; i < poRoot->GetChildCount(); i++ )
    {
        poNode = poRoot->GetChild(i);

        if( EQUAL(poNode->GetValue(),"AUTHORITY") )
        {
            OGRErr eErr = ValidateAuthority(poNode);
            if (eErr != OGRERR_NONE)
                return eErr;
        }
        else if( EQUAL(poNode->GetValue(),"EXTENSION") )
        {


        }
        else
        {
            CPLDebug( "OGRSpatialReference::Validate",
                      "Unexpected child for VERT_DATUM `%s'.\n",
                      poNode->GetValue() );

            return OGRERR_CORRUPT_DATA;
        }
    }

    return OGRERR_NONE;
}
