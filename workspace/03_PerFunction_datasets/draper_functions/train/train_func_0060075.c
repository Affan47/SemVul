AnIsInternalMethod (
    ACPI_PARSE_OBJECT       *Op)
{

    if ((!ACPI_STRCMP (Op->Asl.ExternalName, "\\_OSI")) ||
        (!ACPI_STRCMP (Op->Asl.ExternalName, "_OSI")))
    {
        return (TRUE);
    }

    return (FALSE);
}
