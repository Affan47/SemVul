AeHardwareInterfaces (
    void)
{
#if (!ACPI_REDUCED_HARDWARE)

    ACPI_STATUS             Status;
    UINT32                  Value;


    if (AcpiGbl_ReducedHardware)
    {
        return;
    }

    Status = AcpiWriteBitRegister (ACPI_BITREG_WAKE_STATUS, 1);
    AE_CHECK_OK (AcpiWriteBitRegister, Status);

    Status = AcpiWriteBitRegister (ACPI_BITREG_GLOBAL_LOCK_ENABLE, 1);
    AE_CHECK_OK (AcpiWriteBitRegister, Status);

    Status = AcpiWriteBitRegister (ACPI_BITREG_SLEEP_ENABLE, 1);
    AE_CHECK_OK (AcpiWriteBitRegister, Status);

    Status = AcpiWriteBitRegister (ACPI_BITREG_ARB_DISABLE, 1);
    AE_CHECK_OK (AcpiWriteBitRegister, Status);


    Status = AcpiReadBitRegister (ACPI_BITREG_WAKE_STATUS, &Value);
    AE_CHECK_OK (AcpiReadBitRegister, Status);

    Status = AcpiReadBitRegister (ACPI_BITREG_GLOBAL_LOCK_ENABLE, &Value);
    AE_CHECK_OK (AcpiReadBitRegister, Status);

    Status = AcpiReadBitRegister (ACPI_BITREG_SLEEP_ENABLE, &Value);
    AE_CHECK_OK (AcpiReadBitRegister, Status);

    Status = AcpiReadBitRegister (ACPI_BITREG_ARB_DISABLE, &Value);
    AE_CHECK_OK (AcpiReadBitRegister, Status);

#endif
}
