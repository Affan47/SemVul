DtGetNextSubtable (
    DT_SUBTABLE             *ParentTable,
    DT_SUBTABLE             *ChildTable)
{
    ACPI_FUNCTION_ENTRY ();


    if (!ChildTable)
    {


        return (ParentTable->Child);
    }


    return (ChildTable->Peer);
}
