AcpiUtCopySimpleObject (
    ACPI_OPERAND_OBJECT     *SourceDesc,
    ACPI_OPERAND_OBJECT     *DestDesc)
{
    UINT16                  ReferenceCount;
    ACPI_OPERAND_OBJECT     *NextObject;
    ACPI_STATUS             Status;
    ACPI_SIZE               CopySize;


    ReferenceCount = DestDesc->Common.ReferenceCount;
    NextObject = DestDesc->Common.NextObject;


    CopySize = sizeof (ACPI_OPERAND_OBJECT);
    if (ACPI_GET_DESCRIPTOR_TYPE (SourceDesc) == ACPI_DESC_TYPE_NAMED)
    {
        CopySize = sizeof (ACPI_NAMESPACE_NODE);
    }

    ACPI_MEMCPY (ACPI_CAST_PTR (char, DestDesc),
        ACPI_CAST_PTR (char, SourceDesc), CopySize);


    DestDesc->Common.ReferenceCount = ReferenceCount;
    DestDesc->Common.NextObject = NextObject;


    DestDesc->Common.Flags &= ~AOPOBJ_STATIC_POINTER;


    switch (DestDesc->Common.Type)
    {
    case ACPI_TYPE_BUFFER:


        if ((SourceDesc->Buffer.Pointer) &&
            (SourceDesc->Buffer.Length))
        {
            DestDesc->Buffer.Pointer =
                ACPI_ALLOCATE (SourceDesc->Buffer.Length);
            if (!DestDesc->Buffer.Pointer)
            {
                return (AE_NO_MEMORY);
            }


            ACPI_MEMCPY (DestDesc->Buffer.Pointer,
                SourceDesc->Buffer.Pointer, SourceDesc->Buffer.Length);
        }
        break;

    case ACPI_TYPE_STRING:


        if (SourceDesc->String.Pointer)
        {
            DestDesc->String.Pointer =
                ACPI_ALLOCATE ((ACPI_SIZE) SourceDesc->String.Length + 1);
            if (!DestDesc->String.Pointer)
            {
                return (AE_NO_MEMORY);
            }


            ACPI_MEMCPY (DestDesc->String.Pointer, SourceDesc->String.Pointer,
                (ACPI_SIZE) SourceDesc->String.Length + 1);
        }
        break;

    case ACPI_TYPE_LOCAL_REFERENCE:


        if (SourceDesc->Reference.Class == ACPI_REFCLASS_TABLE)
        {
            break;
        }

        AcpiUtAddReference (SourceDesc->Reference.Object);
        break;

    case ACPI_TYPE_REGION:


        if (DestDesc->Region.Handler)
        {
            AcpiUtAddReference (DestDesc->Region.Handler);
        }
        break;


    case ACPI_TYPE_MUTEX:

        Status = AcpiOsCreateMutex (&DestDesc->Mutex.OsMutex);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }
        break;

    case ACPI_TYPE_EVENT:

        Status = AcpiOsCreateSemaphore (ACPI_NO_UNIT_LIMIT, 0,
                    &DestDesc->Event.OsSemaphore);
        if (ACPI_FAILURE (Status))
        {
            return (Status);
        }
        break;

    default:


        break;
    }

    return (AE_OK);
}
