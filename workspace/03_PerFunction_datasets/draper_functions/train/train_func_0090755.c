AcpiPurgeCachedObjects (
    void)
{
    ACPI_FUNCTION_TRACE (AcpiPurgeCachedObjects);


    (void) AcpiOsPurgeCache (AcpiGbl_StateCache);
    (void) AcpiOsPurgeCache (AcpiGbl_OperandCache);
    (void) AcpiOsPurgeCache (AcpiGbl_PsNodeCache);
    (void) AcpiOsPurgeCache (AcpiGbl_PsNodeExtCache);

    return_ACPI_STATUS (AE_OK);
}
