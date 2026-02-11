getStringValue(OFString &stringVal)
{
    const char *s = OFstatic_cast(char *, getValue());

    if (s != NULL)
        stringVal = s;
    else {

        stringVal = "";
    }
    return errorFlag;
}
