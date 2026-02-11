DtCompileBuffer (
    UINT8                   *Buffer,
    char                    *StringValue,
    DT_FIELD                *Field,
    UINT32                  ByteLength)
{
    ACPI_STATUS             Status;
    char                    Hex[3];
    UINT64                  Value;
    UINT32                  i;
    UINT32                  Count;


    StringValue = DtNormalizeBuffer (StringValue, &Count);

    Hex[2] = 0;
    for (i = 0; i < Count; i++)
    {


        Hex[0] = StringValue[(3 * i)];
        Hex[1] = StringValue[(3 * i) + 1];


        Value = 0;
        Status = DtStrtoul64 (Hex, &Value);
        if (ACPI_FAILURE (Status))
        {
            DtError (ASL_ERROR, ASL_MSG_BUFFER_ELEMENT, Field, MsgBuffer);
            goto Exit;
        }

        Buffer[i] = (UINT8) Value;
    }

Exit:
    ACPI_FREE (StringValue);
    return (ByteLength - Count);
}
