OpnDoBuffer (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_PARSE_OBJECT       *InitializerOp;
    ACPI_PARSE_OBJECT       *BufferLengthOp;


    UINT32                  BufferLength = 0;


    BufferLengthOp = Op->Asl.Child;
    InitializerOp = BufferLengthOp->Asl.Next;


    if ((BufferLengthOp->Asl.ParseOpcode != PARSEOP_INTEGER) &&
        (BufferLengthOp->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG))
    {
        return;
    }


    switch (InitializerOp->Asl.ParseOpcode)
    {
    case PARSEOP_INTEGER:
    case PARSEOP_BYTECONST:
    case PARSEOP_WORDCONST:
    case PARSEOP_DWORDCONST:


        while (InitializerOp)
        {


            InitializerOp->Asl.AmlOpcode      = AML_RAW_DATA_BYTE;
            InitializerOp->Asl.AmlLength      = 1;
            InitializerOp->Asl.ParseOpcode    = PARSEOP_RAW_DATA;

            BufferLength++;
            InitializerOp = ASL_GET_PEER_NODE (InitializerOp);
        }
        break;

    case PARSEOP_STRING_LITERAL:


        BufferLength = strlen (InitializerOp->Asl.Value.String) + 1;

        InitializerOp->Asl.AmlOpcode      = AML_RAW_DATA_BUFFER;
        InitializerOp->Asl.AmlLength      = BufferLength;
        InitializerOp->Asl.ParseOpcode    = PARSEOP_RAW_DATA;
        break;

    case PARSEOP_RAW_DATA:


        return;

    case PARSEOP_DEFAULT_ARG:
        break;

    default:

        AslError (ASL_ERROR, ASL_MSG_INVALID_OPERAND, InitializerOp,
            "Unknown buffer initializer opcode");
        printf ("Unknown buffer initializer opcode [%s]\n",
                        UtGetOpName (InitializerOp->Asl.ParseOpcode));
        return;
    }


    if (BufferLengthOp->Asl.Value.Integer > BufferLength)
    {
        BufferLength = (UINT32) BufferLengthOp->Asl.Value.Integer;
    }

    if (!BufferLength)
    {


        AslError (ASL_REMARK, ASL_MSG_BUFFER_LENGTH, BufferLengthOp, NULL);


    }


    BufferLengthOp->Asl.ParseOpcode   = PARSEOP_INTEGER;
    BufferLengthOp->Asl.AmlOpcode     = AML_DWORD_OP;
    BufferLengthOp->Asl.Value.Integer = BufferLength;

    (void) OpcSetOptimalIntegerSize (BufferLengthOp);


}
