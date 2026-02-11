AcpiOsVprintf (
    const char              *Fmt,
    va_list                 Args)
{
    UINT8                   Flags;
    char                    Buffer[ACPI_VPRINTF_BUFFER_SIZE];


    vsnprintf (Buffer, ACPI_VPRINTF_BUFFER_SIZE, Fmt, Args);

    Flags = AcpiGbl_DbOutputFlags;
    if (Flags & ACPI_DB_REDIRECTABLE_OUTPUT)
    {


        if (AcpiGbl_DebugFile)
        {


            fputs (Buffer, AcpiGbl_DebugFile);
        }
        else
        {


            Flags |= ACPI_DB_CONSOLE_OUTPUT;
        }
    }

    if (Flags & ACPI_DB_CONSOLE_OUTPUT)
    {
        fputs (Buffer, AcpiGbl_OutputFile);
    }
}
