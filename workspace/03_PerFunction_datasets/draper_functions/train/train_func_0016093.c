showfeat_WriteFeat(AjPStr line, char strand, ajint fstart,
			       ajint fend, ajint width, ajint beg, ajint end)
{
    ajint i;
    ajint len;
    ajint pos1;
    ajint pos2;
    float tf;

    len  = end-beg+1;
    tf = ((float)(fstart-beg)/(float)len)*width-(float)1;
    pos1 = (ajint) tf;
    tf = ((float)(fend-beg)/(float)len)*width-(float)1;
    pos2 = (ajint) tf;


    for(i=pos1; i<pos2; i++)
	if(i >= 0 && i < width)

	    if(ajStrGetCharPos(line,i) == ' ')
		ajStrPasteCountK(&line, i, '-', 1);


    if(pos1 >= 0 && pos1 < width)
    {
	if(strand == '+')
	    ajStrPasteCountK(&line, pos1, '|', 1);
	else if(strand == '-')
	    ajStrPasteCountK(&line, pos1, '<', 1);
	else
	    ajStrPasteCountK(&line, pos1, '|', 1);
    }

    if(pos2 >= 0 && pos2 < width)
    {
	if(strand == '+')
	    ajStrPasteCountK(&line, pos2, '>', 1);
	else if(strand == '-')
	    ajStrPasteCountK(&line, pos2, '|', 1);
	else
	    ajStrPasteCountK(&line, pos2, '|', 1);

    }

    return;
}
