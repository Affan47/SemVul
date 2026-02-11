OslListBiosTables (
    void)
{
    ACPI_TABLE_HEADER       *MappedTable = NULL;
    UINT8                   *TableData;
    UINT8                   NumberOfTables;
    UINT8                   ItemSize;
    ACPI_PHYSICAL_ADDRESS   TableAddress = 0;
    ACPI_STATUS             Status = AE_OK;
    UINT32                  i;


    if (Gbl_Revision)
    {
        ItemSize = sizeof (UINT64);
        TableData = ACPI_CAST8 (Gbl_Xsdt) + sizeof (ACPI_TABLE_HEADER);
        NumberOfTables =
            (UINT8) ((Gbl_Xsdt->Header.Length - sizeof (ACPI_TABLE_HEADER))
            / ItemSize);
    }
    else
    {
        ItemSize = sizeof (UINT32);
        TableData = ACPI_CAST8 (Gbl_Rsdt) + sizeof (ACPI_TABLE_HEADER);
        NumberOfTables =
            (UINT8) ((Gbl_Rsdt->Header.Length - sizeof (ACPI_TABLE_HEADER))
            / ItemSize);
    }


    for (i = 0; i < NumberOfTables; ++i, TableData += ItemSize)
    {
        if (Gbl_Revision)
        {
            TableAddress =
                (ACPI_PHYSICAL_ADDRESS) (*ACPI_CAST64 (TableData));
        }
        else
        {
            TableAddress =
                (ACPI_PHYSICAL_ADDRESS) (*ACPI_CAST32 (TableData));
        }

        Status = OslMapTable (TableAddress, NULL, &MappedTable);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }

        OslAddTableToList (MappedTable->Signature, 0);
        OslUnmapTable (MappedTable);
    }

    return (AE_OK);
}
