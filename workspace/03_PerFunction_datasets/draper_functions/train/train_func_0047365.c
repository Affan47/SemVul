AcpiUtPredefinedWarning (
    const char              *ModuleName,
    UINT32                  LineNumber,
    char                    *Pathname,
    UINT8                   NodeFlags,
    const char              *Format,
    ...)
{
    va_list                 ArgList;


    if (NodeFlags & ANOBJ_EVALUATED)
    {
        return;
    }

    AcpiOsPrintf (ACPI_MSG_WARNING "%s: ", Pathname);

    va_start (ArgList, Format);
    AcpiOsVprintf (Format, ArgList);
    ACPI_MSG_SUFFIX;
    va_end (ArgList);
}
