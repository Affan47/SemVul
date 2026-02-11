DtScanFile (
    FILE                    *Handle)
{
    ACPI_STATUS             Status;
    UINT32                  Offset;


    ACPI_FUNCTION_NAME (DtScanFile);


    Gbl_InputByteCount = CmGetFileSize (Handle);
    if (Gbl_InputByteCount == ACPI_UINT32_MAX)
    {
        AslAbort ();
    }

    Gbl_CurrentLineNumber = 0;
    Gbl_CurrentLineOffset = 0;
    Gbl_NextLineOffset = 0;


    while ((Offset = DtGetNextLine (Handle)) != ASL_EOF)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_PARSE, "Line %2.2u/%4.4X - %s",
            Gbl_CurrentLineNumber, Offset, Gbl_CurrentLineBuffer));

        Status = DtParseLine (Gbl_CurrentLineBuffer, Gbl_CurrentLineNumber, Offset);
        if (Status == AE_NOT_FOUND)
        {
            break;
        }
    }


    DtDumpFieldList (Gbl_FieldList);
    return (Gbl_FieldList);
}
