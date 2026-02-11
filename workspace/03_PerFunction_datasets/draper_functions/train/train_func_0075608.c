AcpiDmGetResourceNode (
    ACPI_NAMESPACE_NODE     *BufferNode,
    UINT32                  BitIndex)
{
    ACPI_NAMESPACE_NODE     *Node;
    UINT32                  ByteIndex = ACPI_DIV_8 (BitIndex);


    Node = BufferNode->Child;
    while (Node)
    {


        if ((ByteIndex >= Node->Value) &&
            (ByteIndex < (Node->Value + Node->Length)))
        {
            return (Node);
        }

        Node = Node->Peer;
    }

    return (NULL);
}
