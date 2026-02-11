CgGenerateAmlLengths (
    ACPI_PARSE_OBJECT       *Op)
{
    char                    *Buffer;
    ACPI_STATUS             Status;


    switch (Op->Asl.AmlOpcode)
    {
    case AML_RAW_DATA_BYTE:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlLength = 1;
        return;

    case AML_RAW_DATA_WORD:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlLength = 2;
        return;

    case AML_RAW_DATA_DWORD:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlLength = 4;
        return;

    case AML_RAW_DATA_QWORD:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlLength = 8;
        return;

    case AML_RAW_DATA_BUFFER:


        Op->Asl.AmlOpcodeLength = 0;
        return;

    case AML_RAW_DATA_CHAIN:


        Op->Asl.AmlOpcodeLength = 0;
        return;

    default:

        break;
    }

    switch (Op->Asl.ParseOpcode)
    {
    case PARSEOP_DEFINITIONBLOCK:

        Gbl_TableLength = sizeof (ACPI_TABLE_HEADER) +
                            Op->Asl.AmlSubtreeLength;
        break;

    case PARSEOP_NAMESEG:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlLength = 4;
        Op->Asl.ExternalName = Op->Asl.Value.String;
        break;

    case PARSEOP_NAMESTRING:
    case PARSEOP_METHODCALL:

        if (Op->Asl.CompileFlags & NODE_NAME_INTERNALIZED)
        {
            break;
        }

        Op->Asl.AmlOpcodeLength = 0;
        Status = UtInternalizeName (Op->Asl.Value.String, &Buffer);
        if (ACPI_FAILURE (Status))
        {
            DbgPrint (ASL_DEBUG_OUTPUT,
                "Failure from internalize name %X\n", Status);
            break;
        }

        Op->Asl.ExternalName = Op->Asl.Value.String;
        Op->Asl.Value.String = Buffer;
        Op->Asl.CompileFlags |= NODE_NAME_INTERNALIZED;

        Op->Asl.AmlLength = strlen (Buffer);


        if (Op->Asl.AmlLength == 1)
        {
            Op->Asl.AmlLength = 2;
        }
        break;

    case PARSEOP_STRING_LITERAL:

        Op->Asl.AmlOpcodeLength = 1;


        Op->Asl.AmlLength = strlen (Op->Asl.Value.String) + 1;
        break;

    case PARSEOP_PACKAGE_LENGTH:

        Op->Asl.AmlOpcodeLength = 0;
        Op->Asl.AmlPkgLenBytes = CgGetPackageLenByteCount (Op,
                                    (UINT32) Op->Asl.Value.Integer);
        break;

    case PARSEOP_RAW_DATA:

        Op->Asl.AmlOpcodeLength = 0;
        break;

    case PARSEOP_DEFAULT_ARG:
    case PARSEOP_EXTERNAL:
    case PARSEOP_INCLUDE:
    case PARSEOP_INCLUDE_END:


        break;

    default:

        CgGenerateAmlOpcodeLength (Op);
        break;
    }
}
