ajSeqoutPrintbookFormat(AjPFile outf)
{

    ajint i = 0;
    ajint j = 0;
    AjPStr namestr = NULL;
    AjPList fmtlist;
    AjPStr* names;

    fmtlist = ajListstrNew();

    ajFmtPrintF(outf, "<para>The supported sequence formats are summarised "
                "in the table below. "
                "The columns are as follows: "
                "<emphasis>Input format</emphasis> (format name), "
                "<emphasis>Output format</emphasis> (format name), "
                "<emphasis>Sngl</emphasis> "
                "(indicates whether each sequence is written to a new file. "
                "This behaviour is the default and can be set by the "
                "<option>-ossingle</option> command line qualifier.  "
                "<emphasis>Save</emphasis> (indicates that sequence data is "
                "stored internally and written when the output is closed. "
                "This is needed for 'interleaved' formats such as Phylip "
                "and MSF), <emphasis>Try</emphasis> (indicates whether the "
                "format can be detected automatically on input), "
                "<emphasis>Nuc</emphasis> (\"true\" indicates nucleotide "
                "sequence data may be represented), <emphasis>Pro</emphasis> "
                "(\"true\" indicates protein sequence data may be represented, "
                "<emphasis>Feat</emphasis> (whether the format includes "
                "feature annotation data. "
                "EMBOSS can also read feature data from a separate "
                "feature file).  "
                "<emphasis>Gap</emphasis> (whether the format supports "
                "sequence data with gap characters, for example the results "
                "of an alignment), "
                "<emphasis>Mset</emphasis> (\"true\" indicates that more "
                "than one set of sequences can be stored in a single file. "
                "This is used by, for example, phylogenetic analysis "
                "applications to store many versions of a multiple alignment "
                "for statistical analysis) and "
                "<emphasis>Description</emphasis> (short description of "
                "the format).</para> \n");


    ajFmtPrintF(outf, "<table frame=\"box\" rules=\"cols\">\n");
    ajFmtPrintF(outf, "  <caption>Output sequence formats</caption>\n");
    ajFmtPrintF(outf, "  <thead>\n");
    ajFmtPrintF(outf, "    <tr align=\"center\">\n");
    ajFmtPrintF(outf, "      <th>Input Format</th>\n");
    ajFmtPrintF(outf, "      <th>Sngl</th>\n");
    ajFmtPrintF(outf, "      <th>Save</th>\n");
    ajFmtPrintF(outf, "      <th>Nuc</th>\n");
    ajFmtPrintF(outf, "      <th>Pro</th>\n");
    ajFmtPrintF(outf, "      <th>Feat</th>\n");
    ajFmtPrintF(outf, "      <th>Gap</th>\n");
    ajFmtPrintF(outf, "      <th>Multi</th>\n");
    ajFmtPrintF(outf, "      <th>Description</th>\n");
    ajFmtPrintF(outf, "    </tr>\n");
    ajFmtPrintF(outf, "  </thead>\n");
    ajFmtPrintF(outf, "  <tbody>\n");

    for(i=1; seqOutFormat[i].Name; i++)
    {
	if(!seqOutFormat[i].Alias)
        {
            namestr = ajStrNewC(seqOutFormat[i].Name);
            ajListPush(fmtlist, namestr);
            namestr = NULL;
        }
    }

    ajListSort(fmtlist, &ajStrVcmp);
    ajListstrToarray(fmtlist, &names);

    for(i=0; names[i]; i++)
    {
        for(j=0; seqOutFormat[j].Name; j++)
        {
	    if(ajStrMatchC(names[i],seqOutFormat[j].Name))
            {
                ajFmtPrintF(outf, "    <tr>\n");
                ajFmtPrintF(outf, "      <td>%s</td>\n",
                            seqOutFormat[j].Name);
                ajFmtPrintF(outf, "      <td>%B</td>\n",
                            seqOutFormat[j].Single);
                ajFmtPrintF(outf, "      <td>%B</td>\n",
                            seqOutFormat[j].Save);
                ajFmtPrintF(outf, "      <td>%B</td>\n",
                            seqOutFormat[j].Nucleotide);
                ajFmtPrintF(outf, "      <td>%B</td>\n",
                            seqOutFormat[j].Protein);
                ajFmtPrintF(outf, "      <td>%B</td>\n",
                            seqOutFormat[j].Feature);
                ajFmtPrintF(outf, "      <td>%B</td>\n",
                            seqOutFormat[j].Gap);
                ajFmtPrintF(outf, "      <td>%B</td>\n",
                            seqOutFormat[j].Multiset);
                ajFmtPrintF(outf, "      <td>%s</td>\n",
			seqOutFormat[j].Desc);
                ajFmtPrintF(outf, "    </tr>\n");
            }
        }
    }

    ajFmtPrintF(outf, "  </tbody>\n");
    ajFmtPrintF(outf, "</table>\n");
    ajStrDel(&namestr);

    return;
}
