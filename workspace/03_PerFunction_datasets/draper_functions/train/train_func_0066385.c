AcpiDmIsPldBuffer (
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_PARSE_OBJECT       *ParentOp;


    ParentOp = Op->Common.Parent;
    if (!ParentOp)
    {
        return (FALSE);
    }


    if (ParentOp->Common.AmlOpcode == AML_NAME_OP)
    {
        Node = ParentOp->Common.Node;

        if (ACPI_COMPARE_NAME (Node->Name.Ascii, METHOD_NAME__PLD))
        {
            return (TRUE);
        }

        return (FALSE);
    }


    if (ParentOp->Common.AmlOpcode == AML_PACKAGE_OP)
    {
        ParentOp = ParentOp->Common.Parent;
        if (!ParentOp)
        {
            return (FALSE);
        }

        if (ParentOp->Common.AmlOpcode == AML_NAME_OP)
        {
            Node = ParentOp->Common.Node;

            if (ACPI_COMPARE_NAME (Node->Name.Ascii, METHOD_NAME__PLD))
            {
                return (TRUE);
            }
        }
    }

    return (FALSE);
}
