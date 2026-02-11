adoptNumberFormat(NumberFormat* newNumberFormat)
{
    delete fNumberFormat;
    fNumberFormat = newNumberFormat;
    newNumberFormat->setParseIntegerOnly(TRUE);
}
