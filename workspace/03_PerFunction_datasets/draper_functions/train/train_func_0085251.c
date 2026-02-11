AcpiNsGetPathnameLength (
    ACPI_NAMESPACE_NODE     *Node)
{
    ACPI_SIZE               Size;
    ACPI_NAMESPACE_NODE     *NextNode;


    ACPI_FUNCTION_ENTRY ();


    Size = 0;
    NextNode = Node;

    while (NextNode && (NextNode != AcpiGbl_RootNode))
    {
        if (ACPI_GET_DESCRIPTOR_TYPE (NextNode) != ACPI_DESC_TYPE_NAMED)
        {
            ACPI_ERROR ((AE_INFO,
                "Invalid Namespace Node (%p) while traversing namespace",
                NextNode));
            return (0);
        }
        Size += ACPI_PATH_SEGMENT_LENGTH;
        NextNode = NextNode->Parent;
    }

    if (!Size)
    {
        Size = 1;
    }

    return (Size + 1);
}
