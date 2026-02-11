AcpiDsMethodDataGetNode (
    UINT8                   Type,
    UINT32                  Index,
    ACPI_WALK_STATE         *WalkState,
    ACPI_NAMESPACE_NODE     **Node)
{
    ACPI_FUNCTION_TRACE (DsMethodDataGetNode);


    switch (Type)
    {
    case ACPI_REFCLASS_LOCAL:

        if (Index > ACPI_METHOD_MAX_LOCAL)
        {
            ACPI_ERROR ((AE_INFO,
                "Local index %u is invalid (max %u)",
                Index, ACPI_METHOD_MAX_LOCAL));
            return_ACPI_STATUS (AE_AML_INVALID_INDEX);
        }


        *Node = &WalkState->LocalVariables[Index];
        break;

    case ACPI_REFCLASS_ARG:

        if (Index > ACPI_METHOD_MAX_ARG)
        {
            ACPI_ERROR ((AE_INFO,
                "Arg index %u is invalid (max %u)",
                Index, ACPI_METHOD_MAX_ARG));
            return_ACPI_STATUS (AE_AML_INVALID_INDEX);
        }


        *Node = &WalkState->Arguments[Index];
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Type %u is invalid", Type));
        return_ACPI_STATUS (AE_TYPE);
    }

    return_ACPI_STATUS (AE_OK);
}
