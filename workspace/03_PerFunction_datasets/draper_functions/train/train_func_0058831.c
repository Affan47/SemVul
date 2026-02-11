ajFeatinPrintbookFormat(AjPFile outf)
{
    ajint i = 0;
    ajint j = 0;
    AjPStr namestr = NULL;

    AjPList fmtlist;
    AjPStr* names;

    fmtlist = ajListstrNew();

    ajFmtPrintF(outf, "<para>The supported feature formats are summarised "
                "in the table below. The columns are as follows: "
                "<emphasis>Output format</emphasis> (format name), "
                "<emphasis>Nuc</emphasis> (\"true\" indicates nucleotide "
                "sequence data may be represented), <emphasis>Pro</emphasis> "
                "(\"true\" indicates protein sequence data may be "
                "represented) and <emphasis>Description</emphasis> "
                "(short description of the format).</para>\n\n");

    ajFmtPrintF(outf, "<table frame=\"box\" rules=\"cols\">\n");
    ajFmtPrintF(outf, "  <caption>Input feature formats</caption>\n");
    ajFmtPrintF(outf, "  <thead>\n");
    ajFmtPrintF(outf, "    <tr align=\"center\">\n");
    ajFmtPrintF(outf, "      <th>Output Format</th>\n");
    ajFmtPrintF(outf, "      <th>Nuc</th>\n");
    ajFmtPrintF(outf, "      <th>Pro</th>\n");
    ajFmtPrintF(outf, "      <th>Description</th>\n");
    ajFmtPrintF(outf, "    </tr>\n");
    ajFmtPrintF(outf, "  </thead>\n");
    ajFmtPrintF(outf, "  <tbody>\n");

    for(i=1; featinformatDef[i].Name; i++)
    {
	if(!featinformatDef[i].Alias)
        {
            namestr = ajStrNewC(featinformatDef[i].Name);
            ajListPush(fmtlist, namestr);
            namestr = NULL;
        }
    }

    ajListSort(fmtlist, &ajStrVcmp);
    ajListstrToarray(fmtlist, &names);

    for(i=0; names[i]; i++)
    {
        for(j=0; featinformatDef[j].Name; j++)
        {
            if(ajStrMatchC(names[i],featinformatDef[j].Name))
            {
                ajFmtPrintF(outf, "    <tr>\n");
                ajFmtPrintF(outf, "      <td>%s</td>\n",
                            featinformatDef[j].Name);
                ajFmtPrintF(outf, "      <td>%B</td>\n",
                            featinformatDef[j].Nucleotide);
                ajFmtPrintF(outf, "      <td>%B</td>\n",
                            featinformatDef[j].Protein);
                ajFmtPrintF(outf, "      <td>%s</td>\n",
                            featinformatDef[j].Desc);
                ajFmtPrintF(outf, "    </tr>\n");
            }
        }
    }

    ajFmtPrintF(outf, "  </tbody>\n");
    ajFmtPrintF(outf, "</table>\n");
    ajStrDel(&namestr);

    names = NULL;
    ajListstrFreeData(&fmtlist);

    return;
}
