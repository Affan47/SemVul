HTMLPrologue(FILE * pf, const matchstate * pms,
             const int iGame, char *aszLinks[4], const htmlexporttype UNUSED(het), const htmlexportcss hecss)
{
    char szTitle[100];

    int i;
    int fFirst;


    sprintf(szTitle,
            ngettext("The score (after %d game) is: %s %d, %s %d",
                     "The score (after %d games) is: %s %d, %s %d",
                     pms->cGames), pms->cGames, ap[0].szName, pms->anScore[0], ap[1].szName, pms->anScore[1]);

    if (pms->nMatchTo > 0)
        sprintf(strchr(szTitle, 0),
                ngettext(" (match to %d point%s)",
                         " (match to %d points%s)",
                         pms->nMatchTo),
                pms->nMatchTo,
                pms->fCrawford ? _(", Crawford game") : (pms->fPostCrawford ? _(", post-Crawford play") : ""));

    fprintf(pf,
            "<!DOCTYPE html PUBLIC '-//W3C//DTD XHTML 1.0 Strict//EN' "
            "\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\n"
            "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"en\" "
            "lang=\"en\">\n"
            "<head>\n"
            "<meta name=\"generator\" content=\"%s\" />\n"
            "<meta http-equiv=\"Content-Type\" "
            "content=\"text/html; charset=%s\" />\n"
            "<meta name=\"keywords\" content=\"%s, %s, %s\" />\n"
            "<meta name=\"description\" "
            "content=\"",
            VERSION_STRING,
            GNUBG_CHARSET, ap[0].szName, ap[1].szName, (pms->nMatchTo) ? _("match play") : _("money game"));

    fprintf(pf, _("%s (analysed by %s)"), szTitle, VERSION_STRING);

    fprintf(pf, "\" />\n" "<title>%s</title>\n", szTitle);

    if (hecss == HTML_EXPORT_CSS_HEAD)
        WriteStyleSheet(pf, hecss);
    else if (hecss == HTML_EXPORT_CSS_EXTERNAL)
        fputs("<link title=\"CSS stylesheet\" rel=\"stylesheet\" " "href=\"gnubg.css\" type=\"text/css\" />\n", pf);

    fprintf(pf, "</head>\n" "\n" "<body %s>\n" "<h1>", GetStyle(CLASS_FONT_FAMILY, hecss));

    fprintf(pf, _("Game number %d"), iGame + 1);

    fprintf(pf, "</h1>\n" "<h2>%s</h2>\n", szTitle);


    fFirst = TRUE;

    for (i = 0; i < 4; i++)
        if (aszLinks && aszLinks[i]) {
            if (fFirst) {
                fprintf(pf, "<hr />\n");
                fputs("<p>\n", pf);
                fFirst = FALSE;
            }
            fprintf(pf, "<a href=\"%s\">%s</a>\n", aszLinks[i], gettext(aszLinkText[i]));
        }

    if (!fFirst)
        fputs("</p>\n", pf);

}
