AcpiDmConvertResourceIndexes (
    ACPI_PARSE_OBJECT       *ParseTreeRoot,
    ACPI_NAMESPACE_NODE     *NamespaceRoot)
{
    ACPI_STATUS             Status;
    ACPI_OP_WALK_INFO       Info;
    ACPI_WALK_STATE         *WalkState;


    if (!ParseTreeRoot)
    {
        return;
    }


    WalkState = AcpiDsCreateWalkState (0, ParseTreeRoot, NULL, NULL);
    if (!WalkState)
    {
        return;
    }

    Status = AcpiDsScopeStackPush (NamespaceRoot, NamespaceRoot->Type, WalkState);
    if (ACPI_FAILURE (Status))
    {
        return;
    }

    Info.Flags = 0;
    Info.Level = 0;
    Info.WalkState = WalkState;
    AcpiDmWalkParseTree (ParseTreeRoot, AcpiDmResourceDescendingOp,
        AcpiDmCommonAscendingOp, &Info);
    ACPI_FREE (WalkState);
    return;
}
