AcpiAcquireGlobalLock (
    UINT16                  Timeout,
    UINT32                  *Handle)
{
    ACPI_STATUS             Status;


    if (!Handle)
    {
        return (AE_BAD_PARAMETER);
    }


    AcpiExEnterInterpreter ();

    Status = AcpiExAcquireMutexObject (Timeout,
                AcpiGbl_GlobalLockMutex, AcpiOsGetThreadId ());

    if (ACPI_SUCCESS (Status))
    {


        *Handle = AcpiGbl_GlobalLockHandle;
    }

    AcpiExExitInterpreter ();
    return (Status);
}
