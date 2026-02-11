AcpiDmDumpSlit (
    ACPI_TABLE_HEADER       *Table)
{
    ACPI_STATUS             Status;
    UINT32                  Offset;
    UINT8                   *Row;
    UINT32                  Localities;
    UINT32                  i;
    UINT32                  j;


    Status = AcpiDmDumpTable (Table->Length, 0, Table, 0, AcpiDmTableInfoSlit);
    if (ACPI_FAILURE (Status))
    {
        return;
    }


    Localities = (UINT32) ACPI_CAST_PTR (ACPI_TABLE_SLIT, Table)->LocalityCount;
    Offset = ACPI_OFFSET (ACPI_TABLE_SLIT, Entry[0]);
    Row = (UINT8 *) ACPI_CAST_PTR (ACPI_TABLE_SLIT, Table)->Entry;

    for (i = 0; i < Localities; i++)
    {


        AcpiDmLineHeader2 (Offset, Localities, "Locality", i);
        for  (j = 0; j < Localities; j++)
        {


            if (Offset >= Table->Length)
            {
                AcpiOsPrintf ("\n**** Not enough room in table for all localities\n");
                return;
            }

            AcpiOsPrintf ("%2.2X", Row[j]);
            Offset++;


            if ((j+1) < Localities)
            {
                AcpiOsPrintf (" ");

                if (j && (((j+1) % 16) == 0))
                {
                    AcpiOsPrintf ("\\\n");
                    AcpiDmLineHeader (Offset, 0, NULL);
                }
            }
        }


        AcpiOsPrintf ("\n");
        Row += Localities;
    }
}
