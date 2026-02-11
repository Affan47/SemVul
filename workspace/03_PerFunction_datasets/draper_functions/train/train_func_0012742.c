AcpiEvRemoveGlobalLockHandler (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvRemoveGlobalLockHandler);

    AcpiGbl_GlobalLockPresent = FALSE;
    Status = AcpiRemoveFixedEventHandler (ACPI_EVENT_GLOBAL,
                AcpiEvGlobalLockHandler);

    AcpiOsDeleteLock (AcpiGbl_GlobalLockPendingLock);
    return_ACPI_STATUS (Status);
}
