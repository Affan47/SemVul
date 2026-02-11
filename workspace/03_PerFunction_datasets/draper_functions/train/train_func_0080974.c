AcpiAttachData (
    ACPI_HANDLE             ObjHandle,
    ACPI_OBJECT_HANDLER     Handler,
    void                    *Data)
{
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_STATUS             Status;


    if (!ObjHandle  ||
        !Handler    ||
        !Data)
    {
        return (AE_BAD_PARAMETER);
    }

    Status = AcpiUtAcquireMutex (ACPI_MTX_NAMESPACE);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }


    Node = AcpiNsValidateHandle (ObjHandle);
    if (!Node)
    {
        Status = AE_BAD_PARAMETER;
        goto UnlockAndExit;
    }

    Status = AcpiNsAttachData (Node, Handler, Data);

UnlockAndExit:
    (void) AcpiUtReleaseMutex (ACPI_MTX_NAMESPACE);
    return (Status);
}
