xmlToCmpiType(char *xmlTypeStr)
{
    int i;
    if (xmlTypeStr != NULL)
        for (i = 0; i < (sizeof(xmlCmpiTypes) / sizeof(xmlCmpiType)); i++)
            if (strcasecmp(xmlTypeStr, xmlCmpiTypes[i].str) == 0)
                return xmlCmpiTypes[i].type;
    return CMPI_null;
}
