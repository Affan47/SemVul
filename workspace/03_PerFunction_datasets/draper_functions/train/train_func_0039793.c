AcpiExStore (
    ACPI_OPERAND_OBJECT     *SourceDesc,
    ACPI_OPERAND_OBJECT     *DestDesc,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_OPERAND_OBJECT     *RefDesc = DestDesc;


    ACPI_FUNCTION_TRACE_PTR (ExStore, DestDesc);


    if (!SourceDesc || !DestDesc)
    {
        ACPI_ERROR ((AE_INFO, "Null parameter"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }


    if (ACPI_GET_DESCRIPTOR_TYPE (DestDesc) == ACPI_DESC_TYPE_NAMED)
    {


        Status = AcpiExStoreObjectToNode (SourceDesc,
                    (ACPI_NAMESPACE_NODE *) DestDesc, WalkState,
                    ACPI_IMPLICIT_CONVERSION);

        return_ACPI_STATUS (Status);
    }


    switch (DestDesc->Common.Type)
    {
    case ACPI_TYPE_LOCAL_REFERENCE:

        break;

    case ACPI_TYPE_INTEGER:


        if (DestDesc->Common.Flags & AOPOBJ_AML_CONSTANT)
        {
            return_ACPI_STATUS (AE_OK);
        }


    default:


        ACPI_ERROR ((AE_INFO,
            "Target is not a Reference or Constant object - %s [%p]",
            AcpiUtGetObjectTypeName (DestDesc), DestDesc));

        return_ACPI_STATUS (AE_AML_OPERAND_TYPE);
    }


    switch (RefDesc->Reference.Class)
    {
    case ACPI_REFCLASS_REFOF:


        Status = AcpiExStoreObjectToNode (SourceDesc,
                    RefDesc->Reference.Object,
                    WalkState, ACPI_IMPLICIT_CONVERSION);
        break;

    case ACPI_REFCLASS_INDEX:


        Status = AcpiExStoreObjectToIndex (SourceDesc, RefDesc, WalkState);
        break;

    case ACPI_REFCLASS_LOCAL:
    case ACPI_REFCLASS_ARG:


        Status = AcpiDsStoreObjectToLocal (RefDesc->Reference.Class,
                    RefDesc->Reference.Value, SourceDesc, WalkState);
        break;

    case ACPI_REFCLASS_DEBUG:


        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "**** Write to Debug Object: Object %p %s ****:\n\n",
            SourceDesc, AcpiUtGetObjectTypeName (SourceDesc)));

        ACPI_DEBUG_OBJECT (SourceDesc, 0, 0);
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Unknown Reference Class 0x%2.2X",
            RefDesc->Reference.Class));
        ACPI_DUMP_ENTRY (RefDesc, ACPI_LV_INFO);

        Status = AE_AML_INTERNAL;
        break;
    }

    return_ACPI_STATUS (Status);
}
