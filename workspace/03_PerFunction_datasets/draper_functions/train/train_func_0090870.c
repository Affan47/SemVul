AcpiDsMethodDataGetValue (
    UINT8                   Type,
    UINT32                  Index,
    ACPI_WALK_STATE         *WalkState,
    ACPI_OPERAND_OBJECT     **DestDesc)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_OPERAND_OBJECT     *Object;


    ACPI_FUNCTION_TRACE (DsMethodDataGetValue);


    if (!DestDesc)
    {
        ACPI_ERROR ((AE_INFO, "Null object descriptor pointer"));
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    Status = AcpiDsMethodDataGetNode (Type, Index, WalkState, &Node);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    Object = Node->Object;


    if (!Object)
    {


        if (AcpiGbl_EnableInterpreterSlack)
        {
            Object = AcpiUtCreateIntegerObject ((UINT64) 0);
            if (!Object)
            {
                return_ACPI_STATUS (AE_NO_MEMORY);
            }

            Node->Object = Object;
        }


        else switch (Type)
        {
        case ACPI_REFCLASS_ARG:

            ACPI_ERROR ((AE_INFO,
                "Uninitialized Arg[%u] at node %p",
                Index, Node));

            return_ACPI_STATUS (AE_AML_UNINITIALIZED_ARG);

        case ACPI_REFCLASS_LOCAL:


            return_ACPI_STATUS (AE_AML_UNINITIALIZED_LOCAL);

        default:

            ACPI_ERROR ((AE_INFO, "Not a Arg/Local opcode: 0x%X", Type));
            return_ACPI_STATUS (AE_AML_INTERNAL);
        }
    }


    *DestDesc = Object;
    AcpiUtAddReference (Object);

    return_ACPI_STATUS (AE_OK);
}
