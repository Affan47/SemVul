AcpiUtGetObjectTypeName (
    ACPI_OPERAND_OBJECT     *ObjDesc)
{

    if (!ObjDesc)
    {
        return ("[NULL Object Descriptor]");
    }

    return (AcpiUtGetTypeName (ObjDesc->Common.Type));
}
