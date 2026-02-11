ajNamPrintRsAttr(AjPFile outf, AjBool full)
{
    ajint i;
    AjPStr tmpstr = NULL;
    ajuint maxtmp = 0;

    (void) full;

    ajFmtPrintF(outf, "# Resource attributes\n");
    ajFmtPrintF(outf, "# %-15s %-26s %s\n", "Attribute", "Default", "Comment");
    ajFmtPrintF(outf, "namRsAttrs {\n");

    for(i=0; namRsAttrs[i].Name; i++)
    {
	ajFmtPrintF(outf, "  %-15s", namRsAttrs[i].Name);
	ajFmtPrintS(&tmpstr, "\"%s\"", namRsAttrs[i].Defval);

	if(ajStrGetLen(tmpstr) > maxtmp)
	    maxtmp = ajStrGetLen(tmpstr);

	ajFmtPrintF(outf, " %-36S", tmpstr);
	ajFmtPrintF(outf, " \"%s\"\n", namRsAttrs[i].Comment);
    }

    ajFmtPrintF(outf, "}\n\n");

    if(maxtmp > 36)
        ajWarn("ajNamPrintRsAttr max tmpstr len %u",
               maxtmp);

    ajStrDel(&tmpstr);

    return;
}
