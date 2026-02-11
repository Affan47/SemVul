convert_measure
(
	double d,
	double& dResult,
	const char* pszSpace
)
{


    for(size_t i = kFirstLinearMeasureIdx; i < array_size(kUnits); i++)
    {
        if(str_equal(pszSpace, kUnits[i].pszID))
		{
            dResult = d * kUnits[i].dScale;
			return true;
		}
    }
    CPLError( CE_Failure, CPLE_FileIO,
              "Unknown linear measurement unit: '%s'", pszSpace );
    return false;
}
