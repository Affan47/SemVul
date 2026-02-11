adddelete(FILE * edf3, attrib1_t * attrib)
{
    if (!putvalue(edf3, NULL, attrib->name, attrib->namelen,
                  attrib->value, attrib->valuelen)) {
        log_write_error();
        return IDDS_MM_FIO;
    }
    fprintf(edf3, "changetype: delete\n\n");
    return IDDS_MM_OK;
}
