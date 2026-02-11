Identify( GDALOpenInfo * poOpenInfo )
{
    if (poOpenInfo->nHeaderBytes < 14)
        return FALSE;

    if (EQUALN((const char*)poOpenInfo->pabyHeader,
        "OziExplorer Map Data File Version ", 34) )
        return TRUE;

    if (poOpenInfo->pabyHeader[0] == 0x80 &&
        poOpenInfo->pabyHeader[1] == 0x77)
        return TRUE;

    return poOpenInfo->pabyHeader[0] == 0x78 &&
           poOpenInfo->pabyHeader[1] == 0x77 &&
           poOpenInfo->pabyHeader[6] == 0x40 &&
           poOpenInfo->pabyHeader[7] == 0x00 &&
           poOpenInfo->pabyHeader[8] == 0x01 &&
           poOpenInfo->pabyHeader[9] == 0x00 &&
           poOpenInfo->pabyHeader[10] == 0x36 &&
           poOpenInfo->pabyHeader[11] == 0x04 &&
           poOpenInfo->pabyHeader[12] == 0x00 &&
           poOpenInfo->pabyHeader[13] == 0x00;
}
