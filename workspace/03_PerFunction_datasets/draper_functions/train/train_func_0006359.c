AcpiExAddTable (
    UINT32                  TableIndex,
    ACPI_NAMESPACE_NODE     *ParentNode,
    ACPI_OPERAND_OBJECT     **DdbHandle)
{
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_STATUS             Status;
    ACPI_OWNER_ID           OwnerId;


    ACPI_FUNCTION_TRACE (ExAddTable);


    ObjDesc = AcpiUtCreateInternalObject (ACPI_TYPE_LOCAL_REFERENCE);
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }


    ObjDesc->Common.Flags |= AOPOBJ_DATA_VALID;
    ObjDesc->Reference.Class = ACPI_REFCLASS_TABLE;
    *DdbHandle = ObjDesc;


    ObjDesc->Reference.Value = TableIndex;


    Status = AcpiNsLoadTable (TableIndex, ParentNode);
    if (ACPI_FAILURE (Status))
    {
        AcpiUtRemoveReference (ObjDesc);
        *DdbHandle = NULL;
        return_ACPI_STATUS (Status);
    }


    AcpiExExitInterpreter ();
    AcpiNsExecModuleCodeList ();
    AcpiExEnterInterpreter ();


    Status = AcpiTbGetOwnerId (TableIndex, &OwnerId);
    if (ACPI_SUCCESS (Status))
    {
        AcpiEvUpdateGpes (OwnerId);
    }

    return_ACPI_STATUS (AE_OK);
}
