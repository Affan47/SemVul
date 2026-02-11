Process(RASTERDATA* pbyInputKRGBRaster)
{
    if (pbyInputKRGBRaster == NULL || (pbyInputKRGBRaster->rasterdata[COLORTYPE_BLACK] == NULL && pbyInputKRGBRaster->rasterdata[COLORTYPE_COLOR] == NULL))
    {
        Restart();
        return FALSE;
    }
    started=TRUE;

	if (pbyInputKRGBRaster->rasterdata[COLORTYPE_COLOR])
	{
		BYTE* buff1 = NULL;
		BYTE* buff2 = NULL;
		BYTE* buff3 = NULL;
		BYTE* buff4 = NULL;

		if (StartPlane==K)
		{
			buff1 = Contone;
			if (EndPlane>K)
			{
				buff2 = buff1 + InputWidth;
				buff3 = buff2 + InputWidth;
				buff4 = buff3 + InputWidth;
			}
		}
		else
		{
			buff2 = Contone;
			buff3 = buff2 + InputWidth;
			buff4 = buff3 + InputWidth;
		}

#ifdef APDK_DJ3320
        if (cmap.ulMap3)
        {
		    ColorMatch( InputWidth,
			    cmap.ulMap3,
			    pbyInputKRGBRaster->rasterdata[COLORTYPE_COLOR],
			    buff1,
			    buff2,
			    buff3,
			    buff4
		    );
        }
#endif
        if (cmap.ulMap1)
        {

		    ColorMatch( InputWidth,
			    cmap.ulMap1,
			    pbyInputKRGBRaster->rasterdata[COLORTYPE_COLOR],
			    buff1,
			    buff2,
			    buff3,
			    buff4
		    );
        }

		if (EndPlane > Y && cmap.ulMap2)
		{
			BYTE* buff5 = buff4 + InputWidth;
			BYTE* buff6 = buff5 + InputWidth;

			ColorMatch( InputWidth,
				cmap.ulMap2,
				pbyInputKRGBRaster->rasterdata[COLORTYPE_COLOR],
				NULL,
				buff5,buff6,
				NULL
			);
		}
	}

    iRastersReady = 1;
    iRastersDelivered = 0;
    return TRUE;
}
