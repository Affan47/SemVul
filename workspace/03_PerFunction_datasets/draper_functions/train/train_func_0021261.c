EHattrcat(int32 fid, int32 attrVgrpID, char *attrnames, int32 * strbufsize)
{
    intn            i;

    int32           nObjects;
    int32          *tags;
    int32          *refs;
    int32           vdataID;

    int32           nattr = 0;
    int32           slen;

    char            name[80];
    static const char indxstr[] = "INDXMAP:";

    static const char fvstr[] = "_FV_";
    static const char bsom[] = "_BLKSOM:";


    *strbufsize = 0;


    nObjects = Vntagrefs(attrVgrpID);


    if (nObjects > 0)
    {


	tags = (int32 *) malloc(sizeof(int32) * nObjects);
	if(tags == NULL)
	{
	    HEpush(DFE_NOSPACE,"EHattrcat", __FILE__, __LINE__);
	    return(-1);
	}
	refs = (int32 *) malloc(sizeof(int32) * nObjects);
	if(refs == NULL)
	{
	    HEpush(DFE_NOSPACE,"EHattrcat", __FILE__, __LINE__);
	    free(tags);
	    return(-1);
	}

	Vgettagrefs(attrVgrpID, tags, refs, nObjects);


	for (i = 0; i < nObjects; i++)
	{
	    vdataID = VSattach(fid, *(refs + i), "r");
	    VSgetname(vdataID, name);


	    if (memcmp(name, indxstr, strlen(indxstr)) != 0 &&
		memcmp(name, fvstr, strlen(fvstr)) != 0 &&
		memcmp(name, bsom, strlen(bsom)) != 0)
	    {


		nattr++;
		if (attrnames != NULL)
		{
		    if (nattr == 1)
		    {
			strcpy(attrnames, name);
		    } else
		    {
			strcat(attrnames, ",");
			strcat(attrnames, name);
		    }
		}


		slen = (nattr == 1) ? strlen(name) : strlen(name) + 1;
		*strbufsize += slen;
	    }
	    VSdetach(vdataID);
	}
	free(tags);
	free(refs);
    }
    return (nattr);
}
