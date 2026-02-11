CmdCaption(int code)
{
    char *thecaption;
    char *lst_entry;
    int n, vspace;
    char old_align;
    char number[20];
    char c;

    old_align = getAlignment();
    setAlignment(CENTERED);

    lst_entry = getBracketParam();
    thecaption = getBraceParam();

    if (lst_entry) {
        diagnostics(4, "entering \\caption[%s]{}", lst_entry);
        show_string(4, thecaption, "caption");
        free(lst_entry);
    } else {
        diagnostics(4, "entering \\caption{}");
        show_string(4, thecaption, "caption");
    }

    if (getTexMode() != MODE_VERTICAL)
        CmdEndParagraph(0);
    vspace = getLength("abovecaptionskip");
    setVspace(vspace);
    startParagraph("caption", PARAGRAPH_FIRST);
    fprintRTF("{");

    if (g_processing_figure) {
        incrementCounter("figure");
        ConvertBabelName("FIGURENAME");
        fprintRTF(" ");
        n = getCounter("figure");
        c = 'f';
    } else {
        incrementCounter("table");
        ConvertBabelName("TABLENAME");
        fprintRTF(" ");
        n = getCounter("table");
        c = 't';
    }

    if (g_document_type != FORMAT_ARTICLE &&
        g_document_type != FORMAT_APA)
        snprintf(number, 20, "%d.%d", getCounter("chapter"), n);
    else
        snprintf(number, 20, "%d", n);

    if (g_processing_figure && g_figure_label)
        InsertBookmark(g_figure_label, number);

    else if (g_processing_table && g_table_label)
        InsertBookmark(g_table_label, number);

    else
        fprintRTF("%s", number);

    fprintRTF(": ");
    ConvertString(thecaption);
    fprintRTF("}");

    InsertContentMark(c, number, "  ", thecaption);

    free(thecaption);

    CmdEndParagraph(0);
    vspace = getLength("belowcaptionskip") + getLength("textfloatsep");
    setVspace(vspace);
    setAlignment(old_align);
    diagnostics(4, "exiting CmdCaption");
}
