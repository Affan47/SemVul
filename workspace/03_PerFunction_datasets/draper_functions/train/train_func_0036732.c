AcpiExRegisterOverflow (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    UINT64                  Value)
{

    if (ObjDesc->CommonField.BitLength >= ACPI_INTEGER_BIT_SIZE)
    {


        return (FALSE);
    }

    if (Value >= ((UINT64) 1 << ObjDesc->CommonField.BitLength))
    {


        ACPI_ERROR ((AE_INFO,
            "Index value 0x%8.8X%8.8X overflows field width 0x%X",
            ACPI_FORMAT_UINT64 (Value),
            ObjDesc->CommonField.BitLength));

        return (TRUE);
    }


    return (FALSE);
}
