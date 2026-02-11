AcpiHwWritePort (
    ACPI_IO_ADDRESS         Address,
    UINT32                  Value,
    UINT32                  Width)
{
    ACPI_STATUS             Status;
    UINT32                  i;


    if (AcpiGbl_TruncateIoAddresses)
    {
        Address &= ACPI_UINT16_MAX;
    }


    Status = AcpiHwValidateIoRequest (Address, Width);
    if (ACPI_SUCCESS (Status))
    {
        Status = AcpiOsWritePort (Address, Value, Width);
        return (Status);
    }

    if (Status != AE_AML_ILLEGAL_ADDRESS)
    {
        return (Status);
    }


    for (i = 0; i < Width; i += 8)
    {


        if (AcpiHwValidateIoRequest (Address, 8) == AE_OK)
        {
            Status = AcpiOsWritePort (Address, (Value >> i) & 0xFF, 8);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
        }

        Address++;
    }

    return (AE_OK);
}
