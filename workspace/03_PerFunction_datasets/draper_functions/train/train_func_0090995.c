AcpiDmFieldPredefinedDescription (
    ACPI_PARSE_OBJECT       *Op)
{
#ifdef ACPI_ASL_COMPILER
    ACPI_PARSE_OBJECT       *IndexOp;
    char                    *Tag;
    const ACPI_OPCODE_INFO  *OpInfo;
    const AH_PREDEFINED_NAME *Info;


    if (!Op)
    {
        return;
    }


    if (Op->Common.DisasmFlags & ACPI_PARSEOP_PREDEF_CHECKED)
    {
        return;
    }
    Op->Common.DisasmFlags |= ACPI_PARSEOP_PREDEF_CHECKED;


    OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
    if (!(OpInfo->Flags & AML_CREATE))
    {
        return;
    }


    IndexOp = Op->Common.Value.Arg;
    IndexOp = IndexOp->Common.Next;


    if (IndexOp->Common.AmlOpcode != AML_INT_NAMEPATH_OP)
    {
        return;
    }


    Tag = ACPI_CAST_PTR (char, IndexOp->Common.Node);
    if (!Tag)
    {
        return;
    }


    Info = AcpiAhMatchPredefinedName (Tag);
    if (Info)
    {
        AcpiOsPrintf ("  // %4.4s: %s", Tag,
            ACPI_CAST_PTR (char, Info->Description));
    }

#endif
    return;
}
