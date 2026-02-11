HTMLMatchInfo(FILE * pf, const matchinfo * pmi, const htmlexportcss UNUSED(hecss))
{

    int i;
    char sz[80];
    struct tm tmx;

    if (!pmi->nYear &&
        !pmi->pchRating[0] && !pmi->pchRating[1] &&
        !pmi->pchEvent && !pmi->pchRound && !pmi->pchPlace && !pmi->pchAnnotator && !pmi->pchComment)

        return;

    fputs("\n<!-- Match Information -->\n\n", pf);

    fputs("<hr />", pf);

    fprintf(pf, "<h2>%s</h2>\n", _("Match Information"));

    fputs("<table border=\"0\">\n", pf);


    for (i = 0; i < 2; ++i)
        if (pmi->pchRating[i]) {
            gchar *pch = g_strdup_printf(_("%s's rating"), ap[i].szName);
            HTMLPrintMI(pf, pch, pmi->pchRating[i] ? pmi->pchRating[i] : _("n/a"));
            g_free(pch);
        }


    if (pmi->nYear) {

        tmx.tm_year = pmi->nYear - 1900;
        tmx.tm_mon = pmi->nMonth - 1;
        tmx.tm_mday = pmi->nDay;
        strftime(sz, sizeof(sz), "%B %d, %Y", &tmx);
        HTMLPrintMI(pf, _("Date"), sz);
    }


    HTMLPrintMI(pf, _("Event"), pmi->pchEvent);
    HTMLPrintMI(pf, _("Round"), pmi->pchRound);
    HTMLPrintMI(pf, _("Place"), pmi->pchPlace);
    HTMLPrintMI(pf, _("Annotator"), pmi->pchAnnotator);
    HTMLPrintMI(pf, _("Comment"), pmi->pchComment);

    fputs("</table>\n", pf);

    fputs("\n<!-- End Match Information -->\n\n", pf);

}
