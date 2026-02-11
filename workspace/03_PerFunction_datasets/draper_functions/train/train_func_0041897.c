SWdefidxmap(int32 swathID, char *geodim, char *datadim, int32 index[])

{
    intn            status;

    int32           fid;
    int32           sdInterfaceID;
    int32           attrVgrpID;
    int32           vdataID;
    int32           gsize;
    int32           dsize;
    int32           idOffset = SWIDOFFSET;
    int32           dum;

    uint8          *buf;

    char            mapname[80];
    char            swathname[80];
    char            utlbuf[256];


    status = SWchkswid(swathID, "SWdefidxmap", &fid, &sdInterfaceID, &dum);
    if (status == 0)
    {


	gsize = SWdiminfo(swathID, geodim);

	if (gsize == -1)
	{
	    status = -1;
	    HEpush(DFE_GENAPP, "SWdefidxmap", __FILE__, __LINE__);
	    HEreport("Geolocation dimension name: \"%s\" not found.\n",
		     geodim);
	}


	if (status == 0)
	{
	    dsize = SWdiminfo(swathID, datadim);
	    if (dsize == -1)
	    {
		status = -1;
		HEpush(DFE_GENAPP, "SWdefidxmap", __FILE__, __LINE__);
		HEreport("Data dimension name: \"%s\" not found.\n",
			 datadim);
	    }
	}


	if (status == 0)
	{


	    attrVgrpID = SWXSwath[swathID % idOffset].VIDTable[2];
	    buf = (uint8 *) calloc(4 * gsize, 1);
	    if(buf == NULL)
	    {
		HEpush(DFE_NOSPACE,"SWdefidxmap", __FILE__, __LINE__);
		return(-1);
	    }


	    sprintf(utlbuf, "%s%s%s%s", "INDXMAP:", geodim, "/", datadim);

	    vdataID = VSattach(fid, -1, "w");
	    VSsetname(vdataID, utlbuf);


	    VSsetclass(vdataID, "Attr0.0");


	    VSfdefine(vdataID, "Index", DFNT_INT32, gsize);
	    VSsetfields(vdataID, "Index");
	    memcpy(buf, index, 4 * gsize);


	    VSwrite(vdataID, buf, 1, FULL_INTERLACE);
	    free(buf);


	    Vinsert(attrVgrpID, vdataID);
	    VSdetach(vdataID);


	    sprintf(mapname, "%s%s%s", geodim, "/", datadim);
	    Vgetname(SWXSwath[swathID % idOffset].IDTable, swathname);
	    status = EHinsertmeta(sdInterfaceID, swathname, "s", 2L,
				  mapname, &dum);

	}
    }
    return (status);

}
