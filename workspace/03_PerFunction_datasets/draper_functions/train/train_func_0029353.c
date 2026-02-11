AcpiDmAddToExternalFileList (
    char                    *Pathname)
{
    ACPI_EXTERNAL_FILE      *ExternalFile;
    char                    *LocalPathname;


    if (!Pathname)
    {
        return (AE_OK);
    }

    LocalPathname = ACPI_ALLOCATE (strlen (Pathname) + 1);
    if (!LocalPathname)
    {
        return (AE_NO_MEMORY);
    }

    ExternalFile = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_EXTERNAL_FILE));
    if (!ExternalFile)
    {
        ACPI_FREE (LocalPathname);
        return (AE_NO_MEMORY);
    }


    strcpy (LocalPathname, Pathname);
    ExternalFile->Path = LocalPathname;

    if (AcpiGbl_ExternalFileList)
    {
        ExternalFile->Next = AcpiGbl_ExternalFileList;
    }

    AcpiGbl_ExternalFileList = ExternalFile;
    return (AE_OK);
}
