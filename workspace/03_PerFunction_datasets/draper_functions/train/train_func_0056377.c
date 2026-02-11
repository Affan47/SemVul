ApIsValidChecksum (
    ACPI_TABLE_HEADER       *Table)
{
    ACPI_STATUS             Status;
    ACPI_TABLE_RSDP         *Rsdp;


    if (ACPI_VALIDATE_RSDP_SIG (Table->Signature))
    {


        Rsdp = ACPI_CAST_PTR (ACPI_TABLE_RSDP, Table);
        Status = AcpiTbValidateRsdp (Rsdp);
    }
    else
    {
        Status = AcpiTbVerifyChecksum (Table, Table->Length);
    }

    if (ACPI_FAILURE (Status))
    {
        fprintf (stderr, "%4.4s: Warning: wrong checksum\n",
            Table->Signature);
    }

    return (AE_OK);
}
