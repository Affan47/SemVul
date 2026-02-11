AcpiNsInitOneObject (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_OBJECT_TYPE        Type;
    ACPI_STATUS             Status = AE_OK;
    ACPI_INIT_WALK_INFO     *Info = (ACPI_INIT_WALK_INFO *) Context;
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;
    ACPI_OPERAND_OBJECT     *ObjDesc;


    ACPI_FUNCTION_NAME (NsInitOneObject);


    Info->ObjectCount++;


    Type = AcpiNsGetType (ObjHandle);
    ObjDesc = AcpiNsGetAttachedObject (Node);
    if (!ObjDesc)
    {
        return (AE_OK);
    }


    switch (Type)
    {
    case ACPI_TYPE_REGION:

        Info->OpRegionCount++;
        break;

    case ACPI_TYPE_BUFFER_FIELD:

        Info->FieldCount++;
        break;

    case ACPI_TYPE_LOCAL_BANK_FIELD:

        Info->FieldCount++;
        break;

    case ACPI_TYPE_BUFFER:

        Info->BufferCount++;
        break;

    case ACPI_TYPE_PACKAGE:

        Info->PackageCount++;
        break;

    default:


        return (AE_OK);
    }


    if (ObjDesc->Common.Flags & AOPOBJ_DATA_VALID)
    {
        return (AE_OK);
    }


    AcpiExEnterInterpreter ();


    switch (Type)
    {
    case ACPI_TYPE_REGION:

        Info->OpRegionInit++;
        Status = AcpiDsGetRegionArguments (ObjDesc);
        break;

    case ACPI_TYPE_BUFFER_FIELD:

        Info->FieldInit++;
        Status = AcpiDsGetBufferFieldArguments (ObjDesc);
        break;

    case ACPI_TYPE_LOCAL_BANK_FIELD:

        Info->FieldInit++;
        Status = AcpiDsGetBankFieldArguments (ObjDesc);
        break;

    case ACPI_TYPE_BUFFER:

        Info->BufferInit++;
        Status = AcpiDsGetBufferArguments (ObjDesc);
        break;

    case ACPI_TYPE_PACKAGE:

        Info->PackageInit++;
        Status = AcpiDsGetPackageArguments (ObjDesc);
        break;

    default:


        break;
    }

    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "Could not execute arguments for [%4.4s] (%s)",
            AcpiUtGetNodeName (Node), AcpiUtGetTypeName (Type)));
    }


    AcpiExExitInterpreter ();
    return (AE_OK);
}
