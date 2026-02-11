CmdHAlign(int code)
{
    char *contents, *HA_template, *align;
    char **lines;
    int nlines, ncols,tcols,trepeat,i,line;

    CmdEndParagraph(0);
    contents = getBraceParam();
    HA_ExtractTemplateAndLines(contents, &HA_template, &lines, &nlines);
    free(contents);

    ncols = HA_CountColumnsInHAlign(lines,nlines);
    HA_CountColumnsInTemplate(HA_template,&tcols,&trepeat);
    align = HA_AlignFromTemplate(HA_template, ncols,tcols,trepeat);
    HA_CleanTemplate(HA_template);

    for (line=0; line<nlines; line++) {
        char *s = lines[line];


        fprintRTF("{\\trowd");
        for (i = 1; i <= ncols; i++)
            fprintRTF("\\cellx%d", getLength("textwidth") * (i) / (ncols));
        fprintRTF("\n");
        setTexMode(MODE_HORIZONTAL);

        for (i=1; i<=ncols; i++) {
            char *cell, *cell_template, *cell_text;

            cell = HA_GetCellN(s, i);
            cell_template = HA_GetCellTemplateN(HA_template, i, tcols, trepeat);
            cell_text = HA_ExpandCellWithTemplate(cell_template,cell);
            diagnostics(5,"line=%d, col=%d, align=%c, cell is '%s'",line+1,i,align[i],cell_text);
            free(cell);
            free(cell_template);


            BeginCellRTF(align[i]);
            ConvertString(cell_text);
            EndCellRTF();

            free(cell_text);
        }


        fprintRTF("\\row}\n");
        free(lines[line]);
    }

    setTexMode(MODE_VERTICAL);
    free(align);
    free(lines);
    free(HA_template);
}
