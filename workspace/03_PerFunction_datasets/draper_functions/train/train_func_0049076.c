AcpiUtCopyIobjectToEobject (
    ACPI_OPERAND_OBJECT     *InternalObject,
    ACPI_BUFFER             *RetBuffer)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (UtCopyIobjectToEobject);


    if (InternalObject->Common.Type == ACPI_TYPE_PACKAGE)
    {


        Status = AcpiUtCopyIpackageToEpackage (InternalObject,
                        RetBuffer->Pointer, &RetBuffer->Length);
    }
    else
    {


        Status = AcpiUtCopyIsimpleToEsimple (InternalObject,
                    ACPI_CAST_PTR (ACPI_OBJECT, RetBuffer->Pointer),
                    ACPI_ADD_PTR (UINT8, RetBuffer->Pointer,
                        ACPI_ROUND_UP_TO_NATIVE_WORD (sizeof (ACPI_OBJECT))),
                    &RetBuffer->Length);


        RetBuffer->Length += sizeof (ACPI_OBJECT);
    }

    return_ACPI_STATUS (Status);
}
