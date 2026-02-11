ApDumpTableByName (
    char                    *Signature)
{
    char                    LocalSignature [ACPI_NAME_SIZE + 1];
    UINT32                  Instance;
    ACPI_TABLE_HEADER       *Table;
    ACPI_PHYSICAL_ADDRESS   Address;
    ACPI_STATUS             Status;


    if (strlen (Signature) != ACPI_NAME_SIZE)
    {
        fprintf (stderr,
            "Invalid table signature [%s]: must be exactly 4 characters\n",
            Signature);
        return (-1);
    }


    strcpy (LocalSignature, Signature);
    AcpiUtStrupr (LocalSignature);


    if (ACPI_COMPARE_NAME (LocalSignature, "FADT"))
    {
        strcpy (LocalSignature, ACPI_SIG_FADT);
    }
    else if (ACPI_COMPARE_NAME (LocalSignature, "MADT"))
    {
        strcpy (LocalSignature, ACPI_SIG_MADT);
    }


    for (Instance = 0; Instance < AP_MAX_ACPI_FILES; Instance++)
    {
        Status = AcpiOsGetTableByName (LocalSignature, Instance,
            &Table, &Address);
        if (ACPI_FAILURE (Status))
        {


            if (Status == AE_LIMIT)
            {
                return (0);
            }

            fprintf (stderr,
                "Could not get ACPI table with signature [%s], %s\n",
                LocalSignature, AcpiFormatException (Status));
            return (-1);
        }

        if (ApDumpTableBuffer (Table, Instance, Address))
        {
            return (-1);
        }
        free (Table);
    }


    return (-1);
}
