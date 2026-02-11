MatchType(const Type source,
			  const Type destination)
{
    Type intersection;
    Type baseSource;
    Type baseDestination;


    intersection = source & destination;


    if (NOT intersection OR intersection == DXType::ListType)
    {
	return FALSE;
    }


    if (source      == DXType::ObjectType OR
	destination == DXType::ObjectType)
    {
	return TRUE;
    }


    if ((source & DXType::ListType) AND (NOT (destination & DXType::ListType)))
    {
	return FALSE;
    }


    baseSource      = source      & DXType::ListTypeMask;
    baseDestination = destination & DXType::ListTypeMask;


    if (baseSource == DXType::ScalarType AND
	(baseDestination == DXType::FlagType OR
	 baseDestination == DXType::IntegerType))
    {
	return FALSE;
    }

#ifdef OH_YES_THEY_CAN


    if (baseSource      == DXType::FlagType AND
        baseDestination == DXType::IntegerType)
    {
	return FALSE;
    }
#endif


    return TRUE;
}
