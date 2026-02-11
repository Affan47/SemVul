ajReportPrintwikiFormat(AjPFile outf)
{
    ajint i = 0;
    ajint j = 0;
    AjPStr namestr = NULL;

    ajFmtPrintF(outf, "{| class=\"wikitable sortable\" border=\"2\"\n");
    ajFmtPrintF(outf, "|-\n");
    ajFmtPrintF(outf, "!Format!!Nuc!!Pro!!Header!!Seq||Tags!!"
                "class=\"unsortable\"|Description\n");

    for(i=1; reportFormat[i].Name; i++)
    {
        if(!reportFormat[i].Alias)
        {
            ajFmtPrintF(outf, "|-\n");
            ajStrAssignC(&namestr, reportFormat[i].Name);


            for(j=i+1; reportFormat[j].Name; j++)
            {
                if(reportFormat[j].Write == reportFormat[i].Write)
                {
                    ajFmtPrintAppS(&namestr, "<br>%s", reportFormat[j].Name);
                    if(!reportFormat[j].Alias)
                    {
                        ajWarn("Report output format '%s' same as '%s' "
                               "but not alias",
                               reportFormat[j].Name,
                               reportFormat[i].Name);
                    }
                }
            }
            ajFmtPrintF(outf, "|%S||%B||%B||%B||%B||%d||%s\n",
			namestr,
			reportFormat[i].Nucleotide,
			reportFormat[i].Protein,
			reportFormat[i].Showheader,
			reportFormat[i].Showseq,
			reportFormat[i].Mintags,
			reportFormat[i].Desc);
        }
    }

    ajFmtPrintF(outf, "|}\n");

    ajStrDel(&namestr);

    return;
}
