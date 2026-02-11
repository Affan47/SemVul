AdGetLocalTables (
    void)
{
    ACPI_STATUS             Status;
    ACPI_TABLE_HEADER       TableHeader;
    ACPI_TABLE_HEADER       *NewTable;
    UINT32                  TableIndex;


    ACPI_MOVE_32_TO_32 (TableHeader.Signature, ACPI_SIG_DSDT);
    AcpiOsTableOverride (&TableHeader, &NewTable);
    if (!NewTable)
    {
        fprintf (stderr, "Could not obtain DSDT\n");
        return (AE_NO_ACPI_TABLES);
    }

    AdWriteTable (NewTable, NewTable->Length,
        ACPI_SIG_DSDT, NewTable->OemTableId);


    Status = AcpiTbStoreTable (0, NewTable, NewTable->Length,
                0, &TableIndex);
    if (ACPI_FAILURE (Status))
    {
        fprintf (stderr, "Could not store DSDT\n");
        return (AE_NO_ACPI_TABLES);
    }

    return (AE_OK);
}
