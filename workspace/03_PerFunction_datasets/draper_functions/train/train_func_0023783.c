AcpiPsGetName (
    ACPI_PARSE_OBJECT       *Op)
{


    if (Op->Common.Flags & ACPI_PARSEOP_GENERIC)
    {
        return (0);
    }


    return (Op->Named.Name);
}
