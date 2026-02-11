ajFeatoutPrinthtmlFormat(AjPFile outf)
{
    ajint i = 0;

    ajFmtPrintF(outf, "<table border=3>");
    ajFmtPrintF(outf, "<tr><th>Features Output Format</th><th>Alias</th>\n");
    ajFmtPrintF(outf, "<th>Nuc</th><th>Pro</th>\n");
    ajFmtPrintF(outf, "<th>Description</th></tr>\n");

    for(i=0; featOutFormatDef[i].Name; i++)
    {
	if(!featOutFormatDef[i].Alias)
	    ajFmtPrintF(outf, "<tr><td>\n%-12s\n</td><td>%5B\n</td>"
                        "<td>%5B\n</td><td>%5B\n</td><td>\"%s\"</td></tr>\n",
			featOutFormatDef[i].Name,
			featOutFormatDef[i].Alias,
			featOutFormatDef[i].Nucleotide,
			featOutFormatDef[i].Protein,
			featOutFormatDef[i].Desc);
    }

    ajFmtPrintF(outf, "</table>\n");

    return;
}
