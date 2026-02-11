AcpiDsInitOneObject (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_INIT_WALK_INFO     *Info = (ACPI_INIT_WALK_INFO *) Context;
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *ObjDesc;


    ACPI_FUNCTION_ENTRY ();


    if (Node->OwnerId != Info->OwnerId)
    {
        return (AE_OK);
    }

    Info->ObjectCount++;


    switch (AcpiNsGetType (ObjHandle))
    {
    case ACPI_TYPE_REGION:

        Status = AcpiDsInitializeRegion (ObjHandle);
        if (ACPI_FAILURE (Status))
        {
            ACPI_EXCEPTION ((AE_INFO, Status,
                "During Region initialization %p [%4.4s]",
                ObjHandle, AcpiUtGetNodeName (ObjHandle)));
        }

        Info->OpRegionCount++;
        break;

    case ACPI_TYPE_METHOD:


        Info->MethodCount++;
        ObjDesc = AcpiNsGetAttachedObject (Node);
        if (!ObjDesc)
        {
            break;
        }


        if (ObjDesc->Method.InfoFlags & ACPI_METHOD_SERIALIZED)
        {
            Info->SerialMethodCount++;
            break;
        }

        if (AcpiGbl_AutoSerializeMethods)
        {


            AcpiDsAutoSerializeMethod (Node, ObjDesc);
            if (ObjDesc->Method.InfoFlags & ACPI_METHOD_SERIALIZED)
            {


                Info->SerialMethodCount++;
                Info->SerializedMethodCount++;
                break;
            }
        }

        Info->NonSerialMethodCount++;
        break;

    case ACPI_TYPE_DEVICE:

        Info->DeviceCount++;
        break;

    default:

        break;
    }


    return (AE_OK);
}
