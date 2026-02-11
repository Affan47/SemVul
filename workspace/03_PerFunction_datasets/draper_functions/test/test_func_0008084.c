Parse(trpgToken tok,trpgReadBuffer &buf)
{
    int iVal;

    try
    {
        int ival;
        switch (tok)
        {
        case TRPG_LABEL_PROPERTY_BASIC:
            buf.Get(iVal);
            property->SetFontStyle(iVal);
            buf.Get(iVal);
            property->SetSupport(iVal);
            buf.Get(ival);
            property->SetType(trpgLabelProperty::LabelType(ival));
            break;
        default:
            break;
        }
    }
    catch (...)
    {
        return NULL;
    }

    return property;
}
