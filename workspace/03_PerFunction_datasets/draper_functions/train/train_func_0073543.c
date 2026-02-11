AcpiExResolveObject (
    ACPI_OPERAND_OBJECT     **SourceDescPtr,
    ACPI_OBJECT_TYPE        TargetType,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OPERAND_OBJECT     *SourceDesc = *SourceDescPtr;
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (ExResolveObject);


    switch (TargetType)
    {
    case ACPI_TYPE_BUFFER_FIELD:
    case ACPI_TYPE_LOCAL_REGION_FIELD:
    case ACPI_TYPE_LOCAL_BANK_FIELD:
    case ACPI_TYPE_LOCAL_INDEX_FIELD:


    case ACPI_TYPE_INTEGER:
    case ACPI_TYPE_STRING:
    case ACPI_TYPE_BUFFER:


        if (SourceDesc->Common.Type == ACPI_TYPE_LOCAL_REFERENCE)
        {


            Status = AcpiExResolveToValue (SourceDescPtr, WalkState);
            if (ACPI_FAILURE (Status))
            {
                break;
            }
        }


        if (WalkState->Opcode == AML_COPY_OP)
        {
            break;
        }


        if ((SourceDesc->Common.Type != ACPI_TYPE_INTEGER)    &&
            (SourceDesc->Common.Type != ACPI_TYPE_BUFFER)     &&
            (SourceDesc->Common.Type != ACPI_TYPE_STRING)     &&
            !((SourceDesc->Common.Type == ACPI_TYPE_LOCAL_REFERENCE) &&
                    (SourceDesc->Reference.Class== ACPI_REFCLASS_TABLE)))
        {


            ACPI_ERROR ((AE_INFO,
                "Cannot assign type %s to %s (must be type Int/Str/Buf)",
                AcpiUtGetObjectTypeName (SourceDesc),
                AcpiUtGetTypeName (TargetType)));
            Status = AE_AML_OPERAND_TYPE;
        }
        break;

    case ACPI_TYPE_LOCAL_ALIAS:
    case ACPI_TYPE_LOCAL_METHOD_ALIAS:


        ACPI_ERROR ((AE_INFO, "Store into an unresolved Alias object"));
        Status = AE_AML_INTERNAL;
        break;

    case ACPI_TYPE_PACKAGE:
    default:


        break;
    }

    return_ACPI_STATUS (Status);
}
