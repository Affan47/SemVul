GDdupregion(int32 oldregionID)
{
    intn            i;
    intn            j;
    int32           slendupregion;
    int32           newregionID = -1;


    for (i = 0; i < NGRIDREGN; i++)
    {
	if (GDXRegion[i] == 0)
	{


	    GDXRegion[i] = (struct gridRegion *)
		calloc(1, sizeof(struct gridRegion));
	    if(GDXRegion[i] == NULL)
	    {
		HEpush(DFE_NOSPACE,"GDdupregion", __FILE__, __LINE__);
		return(-1);
	    }


            GDXRegion[i]->fid = GDXRegion[oldregionID]->fid;
            GDXRegion[i]->gridID = GDXRegion[oldregionID]->gridID;
            GDXRegion[i]->xStart = GDXRegion[oldregionID]->xStart;
            GDXRegion[i]->xCount = GDXRegion[oldregionID]->xCount;
            GDXRegion[i]->yStart = GDXRegion[oldregionID]->yStart;
            GDXRegion[i]->yCount = GDXRegion[oldregionID]->yCount;
            GDXRegion[i]->upleftpt[0] = GDXRegion[oldregionID]->upleftpt[0];
            GDXRegion[i]->upleftpt[1] = GDXRegion[oldregionID]->upleftpt[1];
            GDXRegion[i]->lowrightpt[0] = GDXRegion[oldregionID]->lowrightpt[0];
            GDXRegion[i]->lowrightpt[1] = GDXRegion[oldregionID]->lowrightpt[1];
            for (j = 0; j < 8; j++)
            {
                GDXRegion[i]->StartVertical[j] = GDXRegion[oldregionID]->StartVertical[j];
                GDXRegion[i]->StopVertical[j] = GDXRegion[oldregionID]->StopVertical[j];
            }

            for (j=0; j<8; j++)
            {
                if(GDXRegion[oldregionID]->DimNamePtr[j] != NULL)
                {
                    slendupregion = strlen(GDXRegion[oldregionID]->DimNamePtr[j]);
                    GDXRegion[i]->DimNamePtr[j] = (char *) malloc(slendupregion + 1);
                    strcpy(GDXRegion[i]->DimNamePtr[j],GDXRegion[oldregionID]->DimNamePtr[j]);
		}
            }


	    newregionID = i;

	    break;
	}
    }
    return (newregionID);
}
