AcpiNsAttachObject (
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_OPERAND_OBJECT     *Object,
    ACPI_OBJECT_TYPE        Type)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_OPERAND_OBJECT     *LastObjDesc;
    ACPI_OBJECT_TYPE        ObjectType = ACPI_TYPE_ANY;


    ACPI_FUNCTION_TRACE (NsAttachObject);


    if (!Node)
    {


        ACPI_ERROR ((AE_INFO, "Null NamedObj handle"));
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    if (!Object && (ACPI_TYPE_ANY != Type))
    {


        ACPI_ERROR ((AE_INFO,
            "Null object, but type not ACPI_TYPE_ANY"));
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    if (ACPI_GET_DESCRIPTOR_TYPE (Node) != ACPI_DESC_TYPE_NAMED)
    {


        ACPI_ERROR ((AE_INFO, "Invalid handle %p [%s]",
            Node, AcpiUtGetDescriptorName (Node)));
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    if (Node->Object == Object)
    {
        ACPI_DEBUG_PRINT ((ACPI_DB_EXEC,
            "Obj %p already installed in NameObj %p\n",
            Object, Node));

        return_ACPI_STATUS (AE_OK);
    }


    if (!Object)
    {
        ObjDesc    = NULL;
        ObjectType = ACPI_TYPE_ANY;
    }


    else if ((ACPI_GET_DESCRIPTOR_TYPE (Object) == ACPI_DESC_TYPE_NAMED) &&
            ((ACPI_NAMESPACE_NODE *) Object)->Object)
    {


        ObjDesc    = ((ACPI_NAMESPACE_NODE *) Object)->Object;
        ObjectType = ((ACPI_NAMESPACE_NODE *) Object)->Type;
    }


    else
    {
        ObjDesc = (ACPI_OPERAND_OBJECT  *) Object;


        ObjectType = Type;
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Installing %p into Node %p [%4.4s]\n",
        ObjDesc, Node, AcpiUtGetNodeName (Node)));


    if (Node->Object)
    {
        AcpiNsDetachObject (Node);
    }

    if (ObjDesc)
    {


        AcpiUtAddReference (ObjDesc);


        LastObjDesc = ObjDesc;
        while (LastObjDesc->Common.NextObject)
        {
            LastObjDesc = LastObjDesc->Common.NextObject;
        }


        LastObjDesc->Common.NextObject = Node->Object;
    }

    Node->Type     = (UINT8) ObjectType;
    Node->Object   = ObjDesc;

    return_ACPI_STATUS (AE_OK);
}
