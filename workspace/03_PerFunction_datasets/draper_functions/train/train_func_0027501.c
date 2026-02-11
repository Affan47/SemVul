RsDoMemory32FixedDescriptor (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  CurrentByteOffset)
{
    AML_RESOURCE            *Descriptor;
    ACPI_PARSE_OBJECT       *InitializerOp;
    ASL_RESOURCE_NODE       *Rnode;
    UINT16                  ResourceLength;
    UINT32                  i;


    InitializerOp = Op->Asl.Child;
    Rnode = RsAllocateResourceNode (sizeof (AML_RESOURCE_FIXED_MEMORY32));

    Descriptor = Rnode->Buffer;
    Descriptor->FixedMemory32.DescriptorType  = ACPI_RESOURCE_NAME_FIXED_MEMORY32;
    ResourceLength = 9;
    ACPI_MOVE_16_TO_16(&Descriptor->FixedMemory32.ResourceLength, &ResourceLength);


    for (i = 0; InitializerOp; i++)
    {
        switch (i)
        {
        case 0:

            RsSetFlagBits (&Descriptor->FixedMemory32.Flags, InitializerOp, 0, 1);
            RsCreateBitField (InitializerOp, ACPI_RESTAG_READWRITETYPE,
                CurrentByteOffset + ASL_RESDESC_OFFSET (FixedMemory32.Flags), 0);
            break;

        case 1:

            ACPI_MOVE_64_TO_32(&Descriptor->FixedMemory32.Address,
                &InitializerOp->Asl.Value.Integer);
            RsCreateDwordField (InitializerOp, ACPI_RESTAG_BASEADDRESS,
                CurrentByteOffset + ASL_RESDESC_OFFSET (FixedMemory32.Address));
            break;

        case 2:

            ACPI_MOVE_64_TO_32(&Descriptor->FixedMemory32.AddressLength,
                &InitializerOp->Asl.Value.Integer);
            RsCreateDwordField (InitializerOp, ACPI_RESTAG_LENGTH,
                CurrentByteOffset + ASL_RESDESC_OFFSET (FixedMemory32.AddressLength));
            break;

        case 3:

            UtAttachNamepathToOwner (Op, InitializerOp);
            break;

        default:

            AslError (ASL_ERROR, ASL_MSG_RESOURCE_LIST, InitializerOp, NULL);
            break;
        }

        InitializerOp = RsCompleteNodeAndGetNext (InitializerOp);
    }

    return (Rnode);
}
