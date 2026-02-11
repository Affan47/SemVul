AcpiExSystemWaitSemaphore (
    ACPI_SEMAPHORE          Semaphore,
    UINT16                  Timeout)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (ExSystemWaitSemaphore);


    Status = AcpiOsWaitSemaphore (Semaphore, 1, ACPI_DO_NOT_WAIT);
    if (ACPI_SUCCESS (Status))
    {
        return_ACPI_STATUS (Status);
    }

    if (Status == AE_TIME)
    {


        AcpiExExitInterpreter ();

        Status = AcpiOsWaitSemaphore (Semaphore, 1, Timeout);

        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "*** Thread awake after blocking, %s\n",
            AcpiFormatException (Status)));


       AcpiExEnterInterpreter ();
    }

    return_ACPI_STATUS (Status);
}
