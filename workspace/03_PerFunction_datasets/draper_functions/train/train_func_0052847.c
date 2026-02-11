MarkupType(char delim)
{
    uint markupType;

    markupType = 0;

    if((delim == HTML_OPEN_MARKUP) || (delim == HTML_CLOSE_MARKUP))
    {
        markupType |= MARKUP_TYPE_HTML;
    }

    if((delim == htpOpenMarkup) || (delim == htpCloseMarkup))
    {
        markupType |= MARKUP_TYPE_HTP;
    }

    return markupType;
}
