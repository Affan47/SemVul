AcpiExExtractFromField (
    ACPI_OPERAND_OBJECT     *ObjDesc,
    void                    *Buffer,
    UINT32                  BufferLength)
{
    ACPI_STATUS             Status;
    UINT64                  RawDatum;
    UINT64                  MergedDatum;
    UINT32                  FieldOffset = 0;
    UINT32                  BufferOffset = 0;
    UINT32                  BufferTailBits;
    UINT32                  DatumCount;
    UINT32                  FieldDatumCount;
    UINT32                  AccessBitWidth;
    UINT32                  i;


    ACPI_FUNCTION_TRACE (ExExtractFromField);


    if (BufferLength <
        ACPI_ROUND_BITS_UP_TO_BYTES (ObjDesc->CommonField.BitLength))
    {
        ACPI_ERROR ((AE_INFO,
            "Field size %u (bits) is too large for buffer (%u)",
            ObjDesc->CommonField.BitLength, BufferLength));

        return_ACPI_STATUS (AE_BUFFER_OVERFLOW);
    }

    ACPI_MEMSET (Buffer, 0, BufferLength);
    AccessBitWidth = ACPI_MUL_8 (ObjDesc->CommonField.AccessByteWidth);


    if ((ObjDesc->CommonField.StartFieldBitOffset == 0) &&
        (ObjDesc->CommonField.BitLength == AccessBitWidth))
    {
        if (BufferLength >= sizeof (UINT64))
        {
            Status = AcpiExFieldDatumIo (ObjDesc, 0, Buffer, ACPI_READ);
        }
        else
        {


            Status = AcpiExFieldDatumIo (ObjDesc, 0, &RawDatum, ACPI_READ);
            ACPI_MEMCPY (Buffer, &RawDatum, BufferLength);
        }

        return_ACPI_STATUS (Status);
    }


    if (ObjDesc->CommonField.AccessByteWidth > sizeof (UINT64))
    {
        ObjDesc->CommonField.AccessByteWidth = sizeof (UINT64);
        AccessBitWidth = sizeof (UINT64) * 8;
    }


    DatumCount = ACPI_ROUND_UP_TO (
        ObjDesc->CommonField.BitLength, AccessBitWidth);

    FieldDatumCount = ACPI_ROUND_UP_TO (
        ObjDesc->CommonField.BitLength +
        ObjDesc->CommonField.StartFieldBitOffset, AccessBitWidth);


    Status = AcpiExFieldDatumIo (ObjDesc, FieldOffset, &RawDatum, ACPI_READ);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }
    MergedDatum = RawDatum >> ObjDesc->CommonField.StartFieldBitOffset;


    for (i = 1; i < FieldDatumCount; i++)
    {


        FieldOffset += ObjDesc->CommonField.AccessByteWidth;
        Status = AcpiExFieldDatumIo (ObjDesc, FieldOffset,
                    &RawDatum, ACPI_READ);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }


        if (AccessBitWidth - ObjDesc->CommonField.StartFieldBitOffset <
            ACPI_INTEGER_BIT_SIZE)
        {
            MergedDatum |= RawDatum <<
                (AccessBitWidth - ObjDesc->CommonField.StartFieldBitOffset);
        }

        if (i == DatumCount)
        {
            break;
        }


        ACPI_MEMCPY (((char *) Buffer) + BufferOffset, &MergedDatum,
            ACPI_MIN(ObjDesc->CommonField.AccessByteWidth,
                BufferLength - BufferOffset));

        BufferOffset += ObjDesc->CommonField.AccessByteWidth;
        MergedDatum = RawDatum >> ObjDesc->CommonField.StartFieldBitOffset;
    }


    BufferTailBits = ObjDesc->CommonField.BitLength % AccessBitWidth;
    if (BufferTailBits)
    {
        MergedDatum &= ACPI_MASK_BITS_ABOVE (BufferTailBits);
    }


    ACPI_MEMCPY (((char *) Buffer) + BufferOffset, &MergedDatum,
        ACPI_MIN(ObjDesc->CommonField.AccessByteWidth,
            BufferLength - BufferOffset));

    return_ACPI_STATUS (AE_OK);
}
