Write (FILE *file)

	{
	MajorVAR = 2;
	MinorVAR = 0;
	if (fwrite (this,sizeof (DBDataHeader),1,file) != 1)
		{ CMmsgPrint (CMmsgSysError, "File Writing Error in: %s %d",__FILE__,__LINE__); return (DBFault); }
	return (DBSuccess);
	}
