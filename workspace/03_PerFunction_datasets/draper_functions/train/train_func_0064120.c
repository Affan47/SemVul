AdGenerateFilename (
    char                    *Prefix,
    char                    *TableId)
{
    UINT32                  i;
    UINT32                  j;


    for (i = 0; Prefix[i]; i++)
    {
        FilenameBuf[i] = Prefix[i];
    }

    FilenameBuf[i] = '_';
    i++;

    for (j = 0; j < 8 && (TableId[j] != ' ') && (TableId[j] != 0); i++, j++)
    {
        FilenameBuf[i] = TableId[j];
    }

    FilenameBuf[i] = 0;
    strcat (FilenameBuf, ACPI_TABLE_FILE_SUFFIX);
    return (FilenameBuf);
}
