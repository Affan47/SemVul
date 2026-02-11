AcpiSetFirmwareWakingVector (
    UINT32                  PhysicalAddress)
{
    ACPI_FUNCTION_TRACE (AcpiSetFirmwareWakingVector);


    AcpiGbl_FACS->FirmwareWakingVector = PhysicalAddress;


    if ((AcpiGbl_FACS->Length > 32) && (AcpiGbl_FACS->Version >= 1))
    {
        AcpiGbl_FACS->XFirmwareWakingVector = 0;
    }

    return_ACPI_STATUS (AE_OK);
}
