DtCreateAllTemplates (
    void)
{
    ACPI_DMTABLE_DATA       *TableData;
    ACPI_STATUS             Status;


    Status = AdInitialize ();
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    fprintf (stderr, "Creating all supported Template files\n");


    for (TableData = AcpiDmTableData; TableData->Signature; TableData++)
    {


        if (TableData->Template)
        {
            Status = DtCreateOneTemplate (TableData->Signature,
                        TableData);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
        }
    }


    Status = DtCreateOneTemplate (ACPI_SIG_DSDT, NULL);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    Status = DtCreateOneTemplate (ACPI_SIG_SSDT, NULL);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    Status = DtCreateOneTemplate (ACPI_SIG_FACS, NULL);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    Status = DtCreateOneTemplate (ACPI_RSDP_NAME, NULL);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    return (AE_OK);
}
