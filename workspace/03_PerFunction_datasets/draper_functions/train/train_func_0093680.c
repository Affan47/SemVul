Parse(trpgToken tok,trpgReadBuffer &buf)
{
    std::string sVal;
    int iVal;
    float32 fVal;

    try
    {
        switch (tok)
        {
        case TRPG_TEXT_STYLE_BASIC:
            buf.Get(sVal);
            style->SetFont(sVal);
            buf.Get(iVal);
            style->SetBold((iVal ? true : false));
            buf.Get(iVal);
            style->SetItalic((iVal ? true : false));
            buf.Get(iVal);
            style->SetUnderline((iVal ? true : false));
            buf.Get(fVal);
            style->SetCharacterSize(fVal);
            buf.Get(iVal);
            style->SetMaterial(iVal);
            break;
        default:
            break;
        }
    }
    catch (...)
    {
        return NULL;
    }

    return style;
}
