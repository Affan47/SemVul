seqMakeUsa(const AjPSeq thys, AjPStr* usa)
{
    AjPStr tmpstr = NULL;

    ajDebug("seqMakeUsa (Name <%S> Formatstr <%S> Db <%S> "
	    "Entryname <%S> Filename <%S>)\n",
	    thys->Name, thys->Formatstr, thys->Db,
	    thys->Entryname, thys->Filename);

    ajDebug("Begin:%d End:%d Rev:%B Reversed:%B\n",
	    thys->Begin, thys->End, thys->Rev, thys->Reversed);


    if(ajStrGetLen(thys->Db))
	ajFmtPrintS(usa, "%S-id:%S", thys->Db, thys->Entryname);
    else
    {


	if(ajStrMatchC(thys->Formatstr, "asis"))
        {
	    if(thys->Reversed)
	    {
		ajStrAssignS(&tmpstr, thys->Seq);
		ajSeqstrReverse(&tmpstr);
		ajFmtPrintS(usa, "asis::%S", tmpstr);
		ajStrDel(&tmpstr);
	    }
	    else
		ajFmtPrintS(usa, "asis::%S", thys->Seq);
        }
	else if(ajStrGetLen(thys->Entryname))
	    ajFmtPrintS(usa, "%S::%S:%S", thys->Formatstr,
			thys->Filename,thys->Entryname);
	else
	    ajFmtPrintS(usa, "%S::%S", thys->Formatstr,
			thys->Filename);

    }

    ajFmtPrintS(&tmpstr, "[");

    if(thys->Reversed)
    {
	if(thys->End)
	    ajFmtPrintAppS(&tmpstr, "%d", -thys->End);

	ajFmtPrintAppS(&tmpstr, ":");

	if(thys->Begin)
	    ajFmtPrintAppS(&tmpstr, "%d", -thys->Begin);

	ajFmtPrintAppS(&tmpstr, ":r");
    }
    else
    {
	if(thys->Begin)
	    ajFmtPrintAppS(&tmpstr, "%d", thys->Begin);

	ajFmtPrintAppS(&tmpstr, ":");

	if(thys->End)
	    ajFmtPrintAppS(&tmpstr, "%d", thys->End);
    }

    ajFmtPrintAppS(&tmpstr, "]");

    if(ajStrGetLen(tmpstr) > 3)
	ajStrAppendS(usa, tmpstr);

    ajStrDel(&tmpstr);
    ajDebug("      result: <%S>\n",
	    *usa);

    return;
}
