getFormattedName(OFString &formattedName,
                                            const unsigned long pos,
                                            const unsigned int componentGroup)
{
    OFString dicomName;
    OFCondition l_error = getOFString(dicomName, pos);
    if (l_error.good())
        l_error = getFormattedNameFromString(dicomName, formattedName, componentGroup);
    else
        formattedName.clear();
    return l_error;
}
