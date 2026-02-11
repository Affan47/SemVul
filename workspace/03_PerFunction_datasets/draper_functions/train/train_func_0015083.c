GDdefproj(int32 gridID, int32 projcode, int32 zonecode, int32 spherecode,
	  float64 projparm[])
{
    intn            i;
    intn	    projx;
    intn            status = 0;

    int32           fid;
    int32           sdInterfaceID;
    int32           gdVgrpID;
    int32           idOffset = GDIDOFFSET;
    int32           slen;
    float64         EHconvAng();
    char            utlbuf[1024];
    char            projparmbuf[512];

    char            gridname[80];


    status = GDchkgdid(gridID, "GDdefproj", &fid, &sdInterfaceID, &gdVgrpID);

    if (status == 0)
    {


	if (projcode != GCTP_GEO &&
	    projcode != GCTP_UTM &&
	    projcode != GCTP_SPCS)
	{


	    strcpy(projparmbuf, "(");

	    for (i = 0; i < 13; i++)
	    {

		if (projparm[i] == 0.0)
		{
		    strcpy(utlbuf, "0,");
		}
		else
		{

		    if ((int32) projparm[i] == projparm[i])
		    {
			sprintf(utlbuf, "%d%s",
				(int) projparm[i], ",");
		    }

		    else
		    {
			sprintf(utlbuf, "%f%s",	projparm[i], ",");
		    }
		}
		strcat(projparmbuf, utlbuf);
	    }
	    slen = strlen(projparmbuf);


	    projparmbuf[slen - 1] = ')';
	}

	for (projx = 0; Projections[projx].projcode != -1; projx++)
	  {
	    if (projcode == Projections[projx].projcode)
	      {
		break;
	      }
	  }


	if ((projcode == GCTP_GEO))
	{
	    sprintf(utlbuf,
		    "%s%s%s",
		    "\t\tProjection=", Projections[projx].projname, "\n");
	}
	else if (projcode == GCTP_UTM || projcode == GCTP_SPCS)
	{
	    sprintf(utlbuf,
		    "%s%s%s%s%d%s%s%d%s",
		    "\t\tProjection=", Projections[projx].projname, "\n",
		    "\t\tZoneCode=", (int)zonecode, "\n",
		    "\t\tSphereCode=", (int)spherecode, "\n");
	}
	else
	{
	    sprintf(utlbuf,
		    "%s%s%s%s%s%s%s%d%s",
		    "\t\tProjection=", Projections[projx].projname, "\n",
		    "\t\tProjParams=", projparmbuf, "\n",
		    "\t\tSphereCode=", (int)spherecode, "\n");
	}


	Vgetname(GDXGrid[gridID % idOffset].IDTable, gridname);
	status = EHinsertmeta(sdInterfaceID, gridname, "g", 101L,
			      utlbuf, NULL);
    }

    return (status);
}
