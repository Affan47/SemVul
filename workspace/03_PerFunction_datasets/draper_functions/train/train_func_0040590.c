AcpiInstallTableHandler (
    ACPI_TABLE_HANDLER      Handler,
    void                    *Context)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (AcpiInstallTableHandler);


    if (!Handler)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    Status = AcpiUtAcquireMutex (ACPI_MTX_EVENTS);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    if (AcpiGbl_TableHandler)
    {
        Status = AE_ALREADY_EXISTS;
        goto Cleanup;
    }


    AcpiGbl_TableHandler = Handler;
    AcpiGbl_TableHandlerContext = Context;

Cleanup:
    (void) AcpiUtReleaseMutex (ACPI_MTX_EVENTS);
    return_ACPI_STATUS (Status);
}
