AcpiDmDecodeAttribute (
    UINT8                   Attribute)
{

    switch (Attribute)
    {
    case AML_FIELD_ATTRIB_QUICK:

        AcpiOsPrintf ("AttribQuick");
        break;

    case AML_FIELD_ATTRIB_SEND_RCV:

        AcpiOsPrintf ("AttribSendReceive");
        break;

    case AML_FIELD_ATTRIB_BYTE:

        AcpiOsPrintf ("AttribByte");
        break;

    case AML_FIELD_ATTRIB_WORD:

        AcpiOsPrintf ("AttribWord");
        break;

    case AML_FIELD_ATTRIB_BLOCK:

        AcpiOsPrintf ("AttribBlock");
        break;

    case AML_FIELD_ATTRIB_MULTIBYTE:

        AcpiOsPrintf ("AttribBytes");
        break;

    case AML_FIELD_ATTRIB_WORD_CALL:

        AcpiOsPrintf ("AttribProcessCall");
        break;

    case AML_FIELD_ATTRIB_BLOCK_CALL:

        AcpiOsPrintf ("AttribBlockProcessCall");
        break;

    case AML_FIELD_ATTRIB_RAW_BYTES:

        AcpiOsPrintf ("AttribRawBytes");
        break;

    case AML_FIELD_ATTRIB_RAW_PROCESS:

        AcpiOsPrintf ("AttribRawProcessBytes");
        break;

    default:


        AcpiOsPrintf ("0x%2.2X", Attribute);
        break;
    }
}
