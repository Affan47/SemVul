LkIsObjectUsed (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_NAMESPACE_NODE     *Node = ACPI_CAST_PTR (ACPI_NAMESPACE_NODE, ObjHandle);
    ACPI_NAMESPACE_NODE     *Next;
    ACPI_NAME_UNION         tmp;


    if (Node->Flags & ANOBJ_IS_REFERENCED)
    {
        return (AE_OK);
    }

    if (!Node->Op)
    {
        return (AE_OK);
    }


    switch (Node->Type)
    {
    case ACPI_TYPE_DEVICE:
    case ACPI_TYPE_PROCESSOR:
    case ACPI_TYPE_POWER:
    case ACPI_TYPE_THERMAL:
    case ACPI_TYPE_LOCAL_RESOURCE:

        return (AE_OK);

    default:

        break;
    }


    Next = Node->Parent;
    while (Next)
    {
        if (Next->Type == ACPI_TYPE_METHOD)
        {


            ACPI_MOVE_32_TO_32(&tmp.Ascii, Next->Name.Ascii);
            sprintf (MsgBuffer, "Name is within method [%4.4s]",
                tmp.Ascii);
            AslError (ASL_REMARK, ASL_MSG_NOT_REFERENCED,
                LkGetNameOp (Node->Op), MsgBuffer);
            return (AE_OK);
        }

        Next = Next->Parent;
    }


    if (Node->Name.Ascii[0] == '_')
    {
        return (AE_OK);
    }


    AslError (ASL_WARNING2, ASL_MSG_NOT_REFERENCED,
        LkGetNameOp (Node->Op), NULL);
    return (AE_OK);
}
