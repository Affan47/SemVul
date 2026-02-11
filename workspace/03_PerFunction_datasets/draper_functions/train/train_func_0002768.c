DtSetSubtableLength (
    DT_SUBTABLE             *Subtable)
{

    if (!Subtable->LengthField)
    {
        return;
    }

    ACPI_MEMCPY (Subtable->LengthField, &Subtable->TotalLength,
        Subtable->SizeOfLengthField);
}
