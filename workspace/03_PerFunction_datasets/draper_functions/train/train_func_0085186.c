AcpiNsDeleteNamespaceByOwner (
    ACPI_OWNER_ID            OwnerId)
{
    ACPI_NAMESPACE_NODE     *ChildNode;
    ACPI_NAMESPACE_NODE     *DeletionNode;
    ACPI_NAMESPACE_NODE     *ParentNode;
    UINT32                  Level;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE_U32 (NsDeleteNamespaceByOwner, OwnerId);


    if (OwnerId == 0)
    {
        return_VOID;
    }


    Status = AcpiUtAcquireMutex (ACPI_MTX_NAMESPACE);
    if (ACPI_FAILURE (Status))
    {
        return_VOID;
    }

    DeletionNode = NULL;
    ParentNode = AcpiGbl_RootNode;
    ChildNode = NULL;
    Level = 1;


    while (Level > 0)
    {


        ChildNode = AcpiNsGetNextNode (ParentNode, ChildNode);

        if (DeletionNode)
        {
            AcpiNsDeleteChildren (DeletionNode);
            AcpiNsRemoveNode (DeletionNode);
            DeletionNode = NULL;
        }

        if (ChildNode)
        {
            if (ChildNode->OwnerId == OwnerId)
            {


                AcpiNsDetachObject (ChildNode);
            }


            if (ChildNode->Child)
            {


                Level++;
                ParentNode = ChildNode;
                ChildNode  = NULL;
            }
            else if (ChildNode->OwnerId == OwnerId)
            {
                DeletionNode = ChildNode;
            }
        }
        else
        {


            Level--;
            if (Level != 0)
            {
                if (ParentNode->OwnerId == OwnerId)
                {
                    DeletionNode = ParentNode;
                }
            }


            ChildNode = ParentNode;


            ParentNode = ParentNode->Parent;
        }
    }

    (void) AcpiUtReleaseMutex (ACPI_MTX_NAMESPACE);
    return_VOID;
}
