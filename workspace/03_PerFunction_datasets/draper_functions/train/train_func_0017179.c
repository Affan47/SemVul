AcpiDmResourceDescendingOp (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  Level,
    void                    *Context)
{
    ACPI_OP_WALK_INFO       *Info = Context;
    const ACPI_OPCODE_INFO  *OpInfo;
    ACPI_WALK_STATE         *WalkState;
    ACPI_OBJECT_TYPE        ObjectType;
    ACPI_STATUS             Status;


    WalkState = Info->WalkState;
    OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);


    ObjectType = OpInfo->ObjectType;
    if (AcpiNsOpensScope (ObjectType))
    {
        if (Op->Common.Node)
        {

            Status = AcpiDsScopeStackPush (Op->Common.Node, ObjectType, WalkState);
            if (ACPI_FAILURE (Status))
            {
                return (Status);
            }
        }
    }


    AcpiDmCheckResourceReference (Op, WalkState);
    return (AE_OK);
}
