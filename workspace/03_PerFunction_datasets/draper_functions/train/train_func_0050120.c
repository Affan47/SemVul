PIT_CheckLine (line_t* ld)
{
    if (tmbbox[BOXRIGHT] <= ld->bbox[BOXLEFT]
	|| tmbbox[BOXLEFT] >= ld->bbox[BOXRIGHT]
	|| tmbbox[BOXTOP] <= ld->bbox[BOXBOTTOM]
	|| tmbbox[BOXBOTTOM] >= ld->bbox[BOXTOP] )
	return true;

    if (P_BoxOnLineSide (tmbbox, ld) != -1)
	return true;


    if (!ld->backsector)
	return false;

    if (!(tmthing->flags & MF_MISSILE) )
    {
	if ( ld->flags & ML_BLOCKING )
	    return false;

	if ( !tmthing->player && ld->flags & ML_BLOCKMONSTERS )
	    return false;
    }


    P_LineOpening (ld);


    if (opentop < tmceilingz)
    {
	tmceilingz = opentop;
	ceilingline = ld;
    }

    if (openbottom > tmfloorz)
	tmfloorz = openbottom;

    if (lowfloor < tmdropoffz)
	tmdropoffz = lowfloor;


    if (ld->special)
    {
        spechit[numspechit] = ld;
	numspechit++;


        if (numspechit > MAXSPECIALCROSS_ORIGINAL)
        {
            SpechitOverrun(ld);
        }
    }

    return true;
}
