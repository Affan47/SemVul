CommandExportGameHtml(char *sz)
{

    FILE *pf;

    sz = NextToken(&sz);

    if (!plGame) {
        outputl(_("No game in progress (type `new game' to start one)."));
        return;
    }

    if (!sz || !*sz) {
        outputl(_("You must specify a file to export to (see `help export " "game html')."));
        return;
    }

    if (!confirmOverwrite(sz, fConfirmSave))
        return;

    if (!strcmp(sz, "-"))
        pf = stdout;
    else if (!(pf = g_fopen(sz, "w"))) {
        outputerr(sz);
        return;
    }

    if (exsExport.het == HTML_EXPORT_TYPE_GNU)
        check_for_html_images(sz);

    ExportGameHTML(pf, plGame,
                   exsExport.szHTMLPictureURL, exsExport.szHTMLExtension,
                   exsExport.het, exsExport.hecss, getGameNumber(plGame), FALSE, NULL);


    if (pf != stdout)
        fclose(pf);

    setDefaultFileName(sz);


    if (exsExport.hecss == HTML_EXPORT_CSS_EXTERNAL)
        if ((pf = OpenCSS(sz))) {
            WriteStyleSheet(pf, exsExport.hecss);
            fclose(pf);
        }
}
