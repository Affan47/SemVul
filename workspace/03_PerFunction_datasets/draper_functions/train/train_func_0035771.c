AcpiExOpcode_2A_0T_1R (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_OPERAND_OBJECT     **Operand = &WalkState->Operands[0];
    ACPI_OPERAND_OBJECT     *ReturnDesc = NULL;
    ACPI_STATUS             Status = AE_OK;
    BOOLEAN                 LogicalResult = FALSE;


    ACPI_FUNCTION_TRACE_STR (ExOpcode_2A_0T_1R,
        AcpiPsGetOpcodeName (WalkState->Opcode));


    ReturnDesc = AcpiUtCreateInternalObject (ACPI_TYPE_INTEGER);
    if (!ReturnDesc)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }


    if (WalkState->OpInfo->Flags & AML_LOGICAL_NUMERIC)
    {


        Status = AcpiExDoLogicalNumericOp (WalkState->Opcode,
                        Operand[0]->Integer.Value, Operand[1]->Integer.Value,
                        &LogicalResult);
        goto StoreLogicalResult;
    }
    else if (WalkState->OpInfo->Flags & AML_LOGICAL)
    {


        Status = AcpiExDoLogicalOp (WalkState->Opcode, Operand[0],
                    Operand[1], &LogicalResult);
        goto StoreLogicalResult;
    }

    switch (WalkState->Opcode)
    {
    case AML_ACQUIRE_OP:

        Status = AcpiExAcquireMutex (Operand[1], Operand[0], WalkState);
        if (Status == AE_TIME)
        {
            LogicalResult = TRUE;
            Status = AE_OK;
        }
        break;


    case AML_WAIT_OP:

        Status = AcpiExSystemWaitEvent (Operand[1], Operand[0]);
        if (Status == AE_TIME)
        {
            LogicalResult = TRUE;
            Status = AE_OK;
        }
        break;

    default:

        ACPI_ERROR ((AE_INFO, "Unknown AML opcode 0x%X",
            WalkState->Opcode));
        Status = AE_AML_BAD_OPCODE;
        goto Cleanup;
    }


StoreLogicalResult:


    if (LogicalResult)
    {
        ReturnDesc->Integer.Value = ACPI_UINT64_MAX;
    }

Cleanup:


    if (ACPI_FAILURE (Status))
    {
        AcpiUtRemoveReference (ReturnDesc);
    }


    else
    {
        WalkState->ResultObj = ReturnDesc;
    }

    return_ACPI_STATUS (Status);
}
