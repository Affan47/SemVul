SENNextVal(
	FLMBYTE **	 	pSenRV)
{
	FLMUINT			uiTemp;
	FLMBYTE *		pSen = *pSenRV;

	switch (SENValLen( pSen))
	{
		case 1:
		{
			uiTemp = *pSen;
			break;
		}

		case 2:
		{
			uiTemp = ((FLMUINT) (SEN_2B_MASK &*pSen++)) << 8;
			uiTemp += *pSen;
			break;
		}

		case 3:
		{
			uiTemp = ((FLMUINT) (SEN_3B_MASK & (*pSen++))) << 16;
			goto SENNV_2_bytes;
		}

		case 4:
		{
			uiTemp = ((FLMUINT) (SEN_4B_MASK & (*pSen++))) << 24;
			goto SENNV_3_bytes;
		}

		case 5:
		{
			pSen++;
			uiTemp = ((FLMUINT) * pSen++) << 24;
	SENNV_3_bytes:

			uiTemp += ((FLMUINT) * pSen++) << 16;
	SENNV_2_bytes:

			uiTemp += ((FLMUINT) * pSen++) << 8;
			uiTemp += *pSen;
			break;
		}

		default:
		{
			uiTemp = 0;
			break;
		}
	}

	*pSenRV = pSen + 1;
	return (uiTemp);
}
