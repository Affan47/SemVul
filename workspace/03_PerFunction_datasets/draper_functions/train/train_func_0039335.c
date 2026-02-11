GetFeatureElementIndex( const char *pszElement, int nElementLength )

{
    const char *pszLast = m_poState->GetLastComponent();
    size_t      nLenLast = m_poState->GetLastComponentLen();

    if( (nLenLast >= 6 && EQUAL(pszLast+nLenLast-6,"member")) ||
        (nLenLast >= 7 && EQUAL(pszLast+nLenLast-7,"members")) )
    {

    }
    else
    {
        if (nLenLast == 4 && strcmp(pszLast, "dane") == 0)
        {

        }


        else if (nLenLast == 19 && nElementLength == 15 &&
                 strcmp(pszLast, "GeocodeResponseList") == 0 &&
                 strcmp(pszElement, "GeocodedAddress") == 0)
        {
        }
        else if (nLenLast == 22 &&
                 strcmp(pszLast, "DetermineRouteResponse") == 0)
        {


            if (strcmp(pszElement, "RouteInstructionsList") == 0)
                return -1;
        }
        else if (nElementLength == 16 && nLenLast == 21 &&
                 strcmp(pszElement, "RouteInstruction") == 0 &&
                 strcmp(pszLast, "RouteInstructionsList") == 0)
        {
        }


        else if (nLenLast > 6 && strcmp(pszLast + nLenLast - 6, "_layer") == 0 &&
                 nElementLength > 8 && strcmp(pszElement + nElementLength - 8, "_feature") == 0)
        {

        }
        else
            return -1;
    }


    if( !m_bClassListLocked )
        return INT_MAX;


    for( int i = 0; i < m_nClassCount; i++ )
    {
        if( nElementLength == (int)m_papoClass[i]->GetElementNameLen() &&
            memcmp(pszElement,m_papoClass[i]->GetElementName(), nElementLength) == 0 )
            return i;
    }

    return -1;
}
