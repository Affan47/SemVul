AcpiTbPrintTableHeader (
    ACPI_PHYSICAL_ADDRESS   Address,
    ACPI_TABLE_HEADER       *Header)
{
    ACPI_TABLE_HEADER       LocalHeader;


    if (ACPI_COMPARE_NAME (Header->Signature, ACPI_SIG_FACS))
    {


        ACPI_INFO ((AE_INFO, "%-4.4s " ACPI_PRINTF_UINT " %06X",
            Header->Signature, ACPI_FORMAT_TO_UINT (Address),
            Header->Length));
    }
    else if (ACPI_VALIDATE_RSDP_SIG (Header->Signature))
    {


        ACPI_MEMCPY (LocalHeader.OemId,
            ACPI_CAST_PTR (ACPI_TABLE_RSDP, Header)->OemId, ACPI_OEM_ID_SIZE);
        AcpiTbFixString (LocalHeader.OemId, ACPI_OEM_ID_SIZE);

        ACPI_INFO ((AE_INFO, "RSDP " ACPI_PRINTF_UINT " %06X (v%.2d %-6.6s)",
            ACPI_FORMAT_TO_UINT (Address),
            (ACPI_CAST_PTR (ACPI_TABLE_RSDP, Header)->Revision > 0) ?
                ACPI_CAST_PTR (ACPI_TABLE_RSDP, Header)->Length : 20,
            ACPI_CAST_PTR (ACPI_TABLE_RSDP, Header)->Revision,
            LocalHeader.OemId));
    }
    else
    {


        AcpiTbCleanupTableHeader (&LocalHeader, Header);

        ACPI_INFO ((AE_INFO,
            "%-4.4s " ACPI_PRINTF_UINT
            " %06X (v%.2d %-6.6s %-8.8s %08X %-4.4s %08X)",
            LocalHeader.Signature, ACPI_FORMAT_TO_UINT (Address),
            LocalHeader.Length, LocalHeader.Revision, LocalHeader.OemId,
            LocalHeader.OemTableId, LocalHeader.OemRevision,
            LocalHeader.AslCompilerId, LocalHeader.AslCompilerRevision));
    }
}
