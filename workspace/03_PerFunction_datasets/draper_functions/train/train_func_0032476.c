ensHtmlEncodeEntities(AjPStr *Pstr)
{
    if (!Pstr)
        return ajFalse;

    if (!*Pstr)
        return ajFalse;


    ajStrExchangeCC(Pstr, "&", "&amp;");
    ajStrExchangeCC(Pstr, "\"", "&quot;");
    ajStrExchangeCC(Pstr, "<", "&lt;");
    ajStrExchangeCC(Pstr, ">", "&gt;");

    return ajTrue;
}
