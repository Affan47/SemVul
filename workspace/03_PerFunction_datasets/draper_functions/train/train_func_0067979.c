AcpiUtCreatePkgStateAndPush (
    void                    *InternalObject,
    void                    *ExternalObject,
    UINT16                  Index,
    ACPI_GENERIC_STATE      **StateList)
{
    ACPI_GENERIC_STATE       *State;


    ACPI_FUNCTION_ENTRY ();


    State = AcpiUtCreatePkgState (InternalObject, ExternalObject, Index);
    if (!State)
    {
        return (AE_NO_MEMORY);
    }

    AcpiUtPushGenericState (StateList, State);
    return (AE_OK);
}
