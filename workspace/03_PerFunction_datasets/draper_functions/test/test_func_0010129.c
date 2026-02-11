GetStyle(const stylesheetclass ssc, const htmlexportcss hecss)
{

    static char sz[200];

    switch (hecss) {
    case HTML_EXPORT_CSS_INLINE:
        sprintf(sz, "style=\"%s\"", aaszStyleSheetClasses[ssc][1]);
        break;
    case HTML_EXPORT_CSS_EXTERNAL:
    case HTML_EXPORT_CSS_HEAD:
        sprintf(sz, "class=\"%s\"", aaszStyleSheetClasses[ssc][0]);
        break;
    default:
        strcpy(sz, "");
        break;
    }

    return sz;

}
