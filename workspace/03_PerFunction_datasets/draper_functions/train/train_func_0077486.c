AcpiOsTableOverride (
    ACPI_TABLE_HEADER       *ExistingTable,
    ACPI_TABLE_HEADER       **NewTable)
{

    if (!ExistingTable || !NewTable)
    {
        return (AE_BAD_PARAMETER);
    }

    *NewTable = NULL;

#ifdef ACPI_EXEC_APP

    AeTableOverride (ExistingTable, NewTable);
    return (AE_OK);
#else

    return (AE_NO_ACPI_TABLES);
#endif
}
