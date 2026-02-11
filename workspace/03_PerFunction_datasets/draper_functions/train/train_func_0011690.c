AcpiDsMethodError (
    ACPI_STATUS             Status,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_FUNCTION_ENTRY ();


    if (ACPI_SUCCESS (Status) ||
        (Status & AE_CODE_CONTROL))
    {
        return (Status);
    }


    if (AcpiGbl_ExceptionHandler)
    {


        AcpiExExitInterpreter ();


        Status = AcpiGbl_ExceptionHandler (Status,
                    WalkState->MethodNode ?
                        WalkState->MethodNode->Name.Integer : 0,
                    WalkState->Opcode, WalkState->AmlOffset, NULL);
        AcpiExEnterInterpreter ();
    }

    AcpiDsClearImplicitReturn (WalkState);

#ifdef ACPI_DISASSEMBLER
    if (ACPI_FAILURE (Status))
    {


        AcpiDmDumpMethodInfo (Status, WalkState, WalkState->Op);
    }
#endif

    return (Status);
}
