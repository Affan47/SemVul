TrCreateValuedLeafNode (
    UINT32                  ParseOpcode,
    UINT64                  Value)
{
    ACPI_PARSE_OBJECT       *Op;


    Op = TrAllocateNode (ParseOpcode);

    DbgPrint (ASL_PARSE_OUTPUT,
        "\nCreateValuedLeafNode  Ln/Col %u/%u NewNode %p  Op %s  Value %8.8X%8.8X  ",
        Op->Asl.LineNumber, Op->Asl.Column, Op, UtGetOpName(ParseOpcode),
        ACPI_FORMAT_UINT64 (Value));
    Op->Asl.Value.Integer = Value;

    switch (ParseOpcode)
    {
    case PARSEOP_STRING_LITERAL:

        DbgPrint (ASL_PARSE_OUTPUT, "STRING->%s", Value);
        break;

    case PARSEOP_NAMESEG:

        DbgPrint (ASL_PARSE_OUTPUT, "NAMESEG->%s", Value);
        break;

    case PARSEOP_NAMESTRING:

        DbgPrint (ASL_PARSE_OUTPUT, "NAMESTRING->%s", Value);
        break;

    case PARSEOP_EISAID:

        DbgPrint (ASL_PARSE_OUTPUT, "EISAID->%s", Value);
        break;

    case PARSEOP_METHOD:

        DbgPrint (ASL_PARSE_OUTPUT, "METHOD");
        break;

    case PARSEOP_INTEGER:

        DbgPrint (ASL_PARSE_OUTPUT, "INTEGER");
        break;

    default:

        break;
    }

    DbgPrint (ASL_PARSE_OUTPUT, "\n\n");
    return (Op);
}
