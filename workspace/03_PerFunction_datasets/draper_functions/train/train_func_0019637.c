Identify( GDALOpenInfo * poOpenInfo )

{
    static const unsigned char jpc_header[] = {0xff,0x4f};
    static const unsigned char jp2_box_jp[] = {0x6a,0x50,0x20,0x20};

    if( poOpenInfo->nHeaderBytes >= 16
        && (memcmp( poOpenInfo->pabyHeader, jpc_header,
                    sizeof(jpc_header) ) == 0
            || memcmp( poOpenInfo->pabyHeader + 4, jp2_box_jp,
                    sizeof(jp2_box_jp) ) == 0

            || (memcmp( poOpenInfo->pabyHeader, "PG", 2) == 0 &&
                (poOpenInfo->pabyHeader[2] == ' ' || poOpenInfo->pabyHeader[2] == '\t') &&
                (memcmp( poOpenInfo->pabyHeader + 3, "ML", 2) == 0 ||
                 memcmp( poOpenInfo->pabyHeader + 3, "LM", 2) == 0))) )
        return TRUE;

    else
        return FALSE;
}
