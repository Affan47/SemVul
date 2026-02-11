AcpiRsOutString (
    char                    *Title,
    char                    *Value)
{
    AcpiOsPrintf ("%27s : %s", Title, Value);
    if (!*Value)
    {
        AcpiOsPrintf ("[NULL NAMESTRING]");
    }
    AcpiOsPrintf ("\n");
}
