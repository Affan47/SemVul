AcpiExResolveToValue (
    ACPI_OPERAND_OBJECT     **StackPtr,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE_PTR (ExResolveToValue, StackPtr);


    if (!StackPtr || !*StackPtr)
    {
        ACPI_ERROR ((AE_INFO, "Internal - null pointer"));
        return_ACPI_STATUS (AE_AML_NO_OPERAND);
    }


    if (ACPI_GET_DESCRIPTOR_TYPE (*StackPtr) == ACPI_DESC_TYPE_OPERAND)
    {
        Status = AcpiExResolveObjectToValue (StackPtr, WalkState);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }

        if (!*StackPtr)
        {
            ACPI_ERROR ((AE_INFO, "Internal - null pointer"));
            return_ACPI_STATUS (AE_AML_NO_OPERAND);
        }
    }


    if (ACPI_GET_DESCRIPTOR_TYPE (*StackPtr) == ACPI_DESC_TYPE_NAMED)
    {
        Status = AcpiExResolveNodeToValue (
                        ACPI_CAST_INDIRECT_PTR (ACPI_NAMESPACE_NODE, StackPtr),
                        WalkState);
        if (ACPI_FAILURE (Status))
        {
            return_ACPI_STATUS (Status);
        }
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Resolved object %p\n", *StackPtr));
    return_ACPI_STATUS (AE_OK);
}
