ApWriteToBinaryFile (
    ACPI_TABLE_HEADER       *Table,
    UINT32                  Instance)
{
    char                    Filename[ACPI_NAME_SIZE + 16];
    char                    InstanceStr [16];
    FILE                    *File;
    size_t                  Actual;
    UINT32                  TableLength;


    TableLength = ApGetTableLength (Table);


    if (ACPI_VALIDATE_RSDP_SIG (Table->Signature))
    {
        ACPI_MOVE_NAME (Filename, ACPI_RSDP_NAME);
    }
    else
    {
        ACPI_MOVE_NAME (Filename, Table->Signature);
    }
    Filename[0] = (char) ACPI_TOLOWER (Filename[0]);
    Filename[1] = (char) ACPI_TOLOWER (Filename[1]);
    Filename[2] = (char) ACPI_TOLOWER (Filename[2]);
    Filename[3] = (char) ACPI_TOLOWER (Filename[3]);
    Filename[ACPI_NAME_SIZE] = 0;


    if (Instance > 0)
    {
        sprintf (InstanceStr, "%u", Instance);
        strcat (Filename, InstanceStr);
    }

    strcat (Filename, ACPI_TABLE_FILE_SUFFIX);

    if (Gbl_VerboseMode)
    {
        fprintf (stderr,
            "Writing [%4.4s] to binary file: %s 0x%X (%u) bytes\n",
            Table->Signature, Filename, Table->Length, Table->Length);
    }


    File = fopen (Filename, "wb");
    if (!File)
    {
        perror ("Could not open output file");
        return (-1);
    }

    Actual = fwrite (Table, 1, TableLength, File);
    if (Actual != TableLength)
    {
        perror ("Error writing binary output file");
        fclose (File);
        return (-1);
    }

    fclose (File);
    return (0);
}
