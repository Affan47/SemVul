AcpiRsEncodeBitmask (
    UINT8                   *List,
    UINT8                   Count)
{
    UINT32                  i;
    UINT16                  Mask;


    ACPI_FUNCTION_ENTRY ();


    for (i = 0, Mask = 0; i < Count; i++)
    {
        Mask |= (0x1 << List[i]);
    }

    return (Mask);
}
