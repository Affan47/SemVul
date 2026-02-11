AcpiDmMethodFlags (
    ACPI_PARSE_OBJECT       *Op)
{
    UINT32                  Flags;
    UINT32                  Args;


    Op = AcpiPsGetDepthNext (NULL, Op);
    Flags = (UINT8) Op->Common.Value.Integer;
    Args = Flags & 0x07;


    Op->Common.DisasmFlags |= ACPI_PARSEOP_IGNORE;


    AcpiOsPrintf (", %u, ", Args);


    if (!(Flags & 0x08))
    {
        AcpiOsPrintf ("Not");
    }

    AcpiOsPrintf ("Serialized");


    if (Flags & 0xF0)
    {
        AcpiOsPrintf (", %u", Flags >> 4);
    }
}
