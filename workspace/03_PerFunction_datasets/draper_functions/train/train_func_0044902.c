AcpiTbTableOverride (
    ACPI_TABLE_HEADER       *TableHeader,
    ACPI_TABLE_DESC         *TableDesc)
{
    ACPI_STATUS             Status;
    ACPI_TABLE_HEADER       *NewTable = NULL;
    ACPI_PHYSICAL_ADDRESS   NewAddress = 0;
    UINT32                  NewTableLength = 0;
    UINT8                   NewFlags;
    char                    *OverrideType;


    Status = AcpiOsTableOverride (TableHeader, &NewTable);
    if (ACPI_SUCCESS (Status) && NewTable)
    {
        NewAddress = ACPI_PTR_TO_PHYSADDR (NewTable);
        NewTableLength = NewTable->Length;
        NewFlags = ACPI_TABLE_ORIGIN_OVERRIDE;
        OverrideType = "Logical";
        goto FinishOverride;
    }


    Status = AcpiOsPhysicalTableOverride (TableHeader,
        &NewAddress, &NewTableLength);
    if (ACPI_SUCCESS (Status) && NewAddress && NewTableLength)
    {


        NewTable = AcpiOsMapMemory (NewAddress, NewTableLength);
        if (!NewTable)
        {
            ACPI_EXCEPTION ((AE_INFO, AE_NO_MEMORY,
                "%4.4s " ACPI_PRINTF_UINT
                " Attempted physical table override failed",
                TableHeader->Signature,
                ACPI_FORMAT_TO_UINT (TableDesc->Address)));
            return (NULL);
        }

        OverrideType = "Physical";
        NewFlags = ACPI_TABLE_ORIGIN_MAPPED;
        goto FinishOverride;
    }

    return (NULL);


FinishOverride:

    ACPI_INFO ((AE_INFO, "%4.4s " ACPI_PRINTF_UINT
        " %s table override, new table: " ACPI_PRINTF_UINT,
        TableHeader->Signature,
        ACPI_FORMAT_TO_UINT (TableDesc->Address),
        OverrideType, ACPI_FORMAT_TO_UINT (NewTable)));


    AcpiTbDeleteTable (TableDesc);


    TableDesc->Address = NewAddress;
    TableDesc->Pointer = NewTable;
    TableDesc->Length = NewTableLength;
    TableDesc->Flags = NewFlags;

    return (NewTable);
}
