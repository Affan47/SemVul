AcpiDsInitFieldObjects (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_PARSE_OBJECT       *Arg = NULL;
    ACPI_NAMESPACE_NODE     *Node;
    UINT8                   Type = 0;
    UINT32                  Flags;


    ACPI_FUNCTION_TRACE_PTR (DsInitFieldObjects, Op);


    if (!(WalkState->ParseFlags & ACPI_PARSE_EXECUTE))
    {
        if (WalkState->ParseFlags & ACPI_PARSE_DEFERRED_OP)
        {


            return_ACPI_STATUS (AE_OK);
        }

        return_ACPI_STATUS (AE_AML_INTERNAL);
    }


    switch (WalkState->Opcode)
    {
    case AML_FIELD_OP:

        Arg = AcpiPsGetArg (Op, 2);
        Type = ACPI_TYPE_LOCAL_REGION_FIELD;
        break;

    case AML_BANK_FIELD_OP:

        Arg = AcpiPsGetArg (Op, 4);
        Type = ACPI_TYPE_LOCAL_BANK_FIELD;
        break;

    case AML_INDEX_FIELD_OP:

        Arg = AcpiPsGetArg (Op, 3);
        Type = ACPI_TYPE_LOCAL_INDEX_FIELD;
        break;

    default:

        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    Flags = ACPI_NS_NO_UPSEARCH | ACPI_NS_DONT_OPEN_SCOPE |
            ACPI_NS_ERROR_IF_FOUND;


    if (WalkState->MethodNode &&
        !(WalkState->ParseFlags & ACPI_PARSE_MODULE_LEVEL))
    {
        Flags |= ACPI_NS_TEMPORARY;
    }


    while (Arg)
    {


        if (Arg->Common.AmlOpcode == AML_INT_NAMEDFIELD_OP)
        {
            Status = AcpiNsLookup (WalkState->ScopeInfo,
                        (char *) &Arg->Named.Name, Type, ACPI_IMODE_LOAD_PASS1,
                        Flags, WalkState, &Node);
            if (ACPI_FAILURE (Status))
            {
                ACPI_ERROR_NAMESPACE ((char *) &Arg->Named.Name, Status);
                if (Status != AE_ALREADY_EXISTS)
                {
                    return_ACPI_STATUS (Status);
                }


                Status = AE_OK;
            }

            Arg->Common.Node = Node;
        }


        Arg = Arg->Common.Next;
    }

    return_ACPI_STATUS (AE_OK);
}
