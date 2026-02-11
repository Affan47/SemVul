SWdupregion(int32 oldregionID)
{
    intn            i;

    int32           newregionID = -1;


    for (i = 0; i < NSWATHREGN; i++)
    {
	if (SWXRegion[i] == 0)
	{


	    SWXRegion[i] = (struct swathRegion *)
		calloc(1, sizeof(struct swathRegion));
	    if(SWXRegion[i] == NULL)
	    {
		HEpush(DFE_NOSPACE,"SWdupregion", __FILE__, __LINE__);
		return(-1);
	    }


	    *SWXRegion[i] = *SWXRegion[oldregionID];


	    newregionID = i;

	    break;
	}
    }

    return (newregionID);
}
