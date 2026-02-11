AslDetectSourceFileType (
    ASL_FILE_INFO           *Info)
{
    char                    *FileChar;
    UINT8                   Type;
    ACPI_STATUS             Status;


    Status = FlCheckForAcpiTable (Info->Handle);
    if (ACPI_SUCCESS (Status))
    {
        Type = ASL_INPUT_TYPE_ACPI_TABLE;
        goto Cleanup;
    }


    Status = FlCheckForAscii (Info->Handle, Info->Filename, TRUE);
    if (ACPI_FAILURE (Status))
    {
        printf ("Non-ascii input file - %s\n", Info->Filename);

        if (!Gbl_IgnoreErrors)
        {
            Type = ASL_INPUT_TYPE_BINARY;
            goto Cleanup;
        }
    }


    while (fgets (Gbl_CurrentLineBuffer, Gbl_LineBufferSize, Info->Handle))
    {


        FileChar = Gbl_CurrentLineBuffer;
        while (*FileChar)
        {
            *FileChar = (char) toupper ((int) *FileChar);
            FileChar++;
        }


        if (strstr (Gbl_CurrentLineBuffer, "DEFINITIONBLOCK"))
        {


            Type = ASL_INPUT_TYPE_ASCII_ASL;
            goto Cleanup;
        }
    }


    Type = ASL_INPUT_TYPE_ASCII_DATA;

Cleanup:


    fseek (Info->Handle, 0, SEEK_SET);
    return (Type);
}
