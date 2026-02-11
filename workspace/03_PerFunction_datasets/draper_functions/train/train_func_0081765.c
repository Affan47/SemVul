GDgetfillvalue(int32 gridID, char *fieldname, VOIDP fillval)
{
    intn            status;

    int32           nt;
    int32           dims[8];
    int32           dum;

    char            name[80];

    status = GDchkgdid(gridID, "GDgetfillvalue", &dum, &dum, &dum);


    if (status == 0)
    {

	status = GDfieldinfo(gridID, fieldname, &dum, dims, &nt, NULL);

	if (status == 0)
	{

	    strcpy(name, "_FV_");
	    strcat(name, fieldname);
	    status = GDreadattr(gridID, name, fillval);
	}
	else
	{
	    HEpush(DFE_GENAPP, "GDgetfillvalue", __FILE__, __LINE__);
	    HEreport("Fieldname \"%s\" does not exist.\n", fieldname);
	}

    }
    return (status);
}
