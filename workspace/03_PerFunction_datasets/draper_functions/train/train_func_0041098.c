AcpiPsDisplayObjectPathname (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_BUFFER             Buffer;
    UINT32                  DebugLevel;


    DebugLevel = AcpiDbgLevel;
    AcpiDbgLevel = 0;


    Node = Op->Common.Node;
    if (!Node)
    {


        Status = AcpiNsLookup (WalkState->ScopeInfo, Op->Common.Value.String,
                    ACPI_TYPE_ANY, ACPI_IMODE_EXECUTE, ACPI_NS_SEARCH_PARENT,
                    WalkState, &(Node));

        if (ACPI_FAILURE (Status))
        {


            AcpiOsPrintf ("  [Path not found]");
            goto Exit;
        }


        Op->Common.Node = Node;
    }


    Buffer.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    Status = AcpiNsHandleToPathname (Node, &Buffer);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("****Could not get pathname****)");
        goto Exit;
    }

    AcpiOsPrintf ("  (Path %s)", (char *) Buffer.Pointer);
    ACPI_FREE (Buffer.Pointer);


Exit:


    AcpiDbgLevel = DebugLevel;
    return (Status);
}
