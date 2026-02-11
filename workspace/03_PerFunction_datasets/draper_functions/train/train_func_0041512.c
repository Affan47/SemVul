InitializeAcpi (
    void)
{
    ACPI_STATUS             Status;


    Status = AcpiInitializeSubsystem ();
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }


    Status = AcpiReallocateRootTable ();
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }


    Status = AcpiLoadTables ();
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }


    Status = InstallHandlers ();
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status, "While installing handlers"));
        return (Status);
    }


    Status = AcpiEnableSubsystem (ACPI_FULL_INITIALIZATION);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }


    Status = AcpiInitializeObjects (ACPI_FULL_INITIALIZATION);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    return (AE_OK);
}
