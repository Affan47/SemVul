AcpiDsMethodDataSetValue (
    UINT8                   Type,
    UINT32                  Index,
    ACPI_OPERAND_OBJECT     *Object,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;


    ACPI_FUNCTION_TRACE (DsMethodDataSetValue);


    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
        "NewObj %p Type %2.2X, Refs=%u [%s]\n", Object,
        Type, Object->Common.ReferenceCount,
        AcpiUtGetTypeName (Object->Common.Type)));


    Status = AcpiDsMethodDataGetNode (Type, Index, WalkState, &Node);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    AcpiUtAddReference (Object);


    Node->Object = Object;
    return_ACPI_STATUS (Status);
}
