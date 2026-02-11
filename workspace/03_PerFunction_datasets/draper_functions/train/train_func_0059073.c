AcpiSetGpe (
    ACPI_HANDLE             GpeDevice,
    UINT32                  GpeNumber,
    UINT8                   Action)
{
    ACPI_GPE_EVENT_INFO     *GpeEventInfo;
    ACPI_STATUS             Status;
    ACPI_CPU_FLAGS          Flags;


    ACPI_FUNCTION_TRACE (AcpiSetGpe);


    Flags = AcpiOsAcquireLock (AcpiGbl_GpeLock);


    GpeEventInfo = AcpiEvGetGpeEventInfo (GpeDevice, GpeNumber);
    if (!GpeEventInfo)
    {
        Status = AE_BAD_PARAMETER;
        goto UnlockAndExit;
    }


    switch (Action)
    {
    case ACPI_GPE_ENABLE:

        Status = AcpiEvEnableGpe (GpeEventInfo);
        break;

    case ACPI_GPE_DISABLE:

        Status = AcpiHwLowSetGpe (GpeEventInfo, ACPI_GPE_DISABLE);
        break;

    default:

        Status = AE_BAD_PARAMETER;
        break;
    }

UnlockAndExit:
    AcpiOsReleaseLock (AcpiGbl_GpeLock, Flags);
    return_ACPI_STATUS (Status);
}
