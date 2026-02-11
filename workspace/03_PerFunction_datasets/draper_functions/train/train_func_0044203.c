AcpiDmClearExternalFileList (
    void)
{
    ACPI_EXTERNAL_FILE      *NextExternal;


    while (AcpiGbl_ExternalFileList)
    {
        NextExternal = AcpiGbl_ExternalFileList->Next;
        ACPI_FREE (AcpiGbl_ExternalFileList->Path);
        ACPI_FREE (AcpiGbl_ExternalFileList);
        AcpiGbl_ExternalFileList = NextExternal;
    }
}
