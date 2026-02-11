cirdna_ReadInput(AjPFile infile,
                               float *Start, float *End)
{
    AjPStr line;

    AjBool foundstart = ajFalse;
    AjBool foundend   = ajFalse;

    line = ajStrNew();
    while(ajReadlineTrim(infile, &line))
    {

	if(ajStrPrefixC(line, "Start"))
        {
            foundstart = ajTrue;
	    if(sscanf(ajStrGetPtr(line), "%*s%f", Start) != 1)
                return ajFalse;
        }

	if(ajStrPrefixC(line, "End"))
        {
            foundend = ajTrue;
	    if(sscanf(ajStrGetPtr(line), "%*s%f", End) != 1)
            {
                ajStrDel(&line);
                return ajFalse;
            }
        }
    }

    ajStrDel(&line);

    if(!foundstart || !foundend)
    {
        ajWarn("Missing Start and/or End line(s) in input file");
        return ajFalse;
    }


    return ajTrue;;
}
