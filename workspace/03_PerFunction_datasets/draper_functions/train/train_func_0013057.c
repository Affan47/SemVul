AcpiEvExecuteRegMethods (
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_ADR_SPACE_TYPE     SpaceId)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvExecuteRegMethods);


    Status = AcpiNsWalkNamespace (ACPI_TYPE_ANY, Node, ACPI_UINT32_MAX,
                ACPI_NS_WALK_UNLOCK, AcpiEvRegRun, NULL,
                &SpaceId, NULL);


    if (SpaceId == ACPI_ADR_SPACE_EC)
    {
        AcpiEvOrphanEcRegMethod (Node);
    }

    return_ACPI_STATUS (Status);
}
