AcpiDmDumpBuffer (
    void                    *Table,
    UINT32                  BufferOffset,
    UINT32                  Length,
    UINT32                  AbsoluteOffset,
    char                    *Header)
{
    UINT8                   *Buffer;
    UINT32                  i;


    if (!Length)
    {
        return;
    }

    Buffer = ACPI_CAST_PTR (UINT8, Table) + BufferOffset;
    i = 0;

    while (i < Length)
    {
        if (!(i % 16))
        {
            AcpiOsPrintf ("\n");
            AcpiDmLineHeader (AbsoluteOffset,
                ((Length - i) > 16) ? 16 : (Length - i), Header);
            Header = NULL;
        }

        AcpiOsPrintf ("%.02X ", *Buffer);
        i++;
        Buffer++;
        AbsoluteOffset++;
    }

    AcpiOsPrintf ("\n");
}
