SWperiodinfo(int32 swathID, int32 periodID, char *fieldname,
	     int32 * ntype, int32 * rank, int32 dims[], int32 * size)
{
    intn            status;


    timeflag = 1;


    status = SWregioninfo(swathID, periodID, fieldname, ntype, rank,
			  dims, size);
    if (status != 0) timeflag = 0;
    return (status);
}
