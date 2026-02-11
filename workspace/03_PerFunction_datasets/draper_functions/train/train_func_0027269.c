RsDoMemory32Descriptor (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  CurrentByteOffset)
{
    AML_RESOURCE            *Descriptor;
    ACPI_PARSE_OBJECT       *InitializerOp;
    ACPI_PARSE_OBJECT       *MinOp = NULL;
    ACPI_PARSE_OBJECT       *MaxOp = NULL;
    ACPI_PARSE_OBJECT       *LengthOp = NULL;
    ACPI_PARSE_OBJECT       *AlignOp = NULL;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  i;


    InitializerOp = Op->Asl.Child;
    Rnode = RsAllocateResourceNode (sizeof (AML_RESOURCE_MEMORY32));

    Descriptor = Rnode->Buffer;
    Descriptor->Memory32.DescriptorType  = ACPI_RESOURCE_NAME_MEMORY32;
    Descriptor->Memory32.ResourceLength = 17;


    for (i = 0; InitializerOp; i++)
    {
        switch (i)
        {
        case 0:

            RsSetFlagBits (&Descriptor->Memory32.Flags, InitializerOp, 0, 1);
            RsCreateBitField (InitializerOp, ACPI_RESTAG_READWRITETYPE,
                CurrentByteOffset + ASL_RESDESC_OFFSET (Memory32.Flags), 0);
            break;

        case 1:

            Descriptor->Memory32.Minimum = (UINT32) InitializerOp->Asl.Value.Integer;
            RsCreateDwordField (InitializerOp, ACPI_RESTAG_MINADDR,
                CurrentByteOffset + ASL_RESDESC_OFFSET (Memory32.Minimum));
            MinOp = InitializerOp;
            break;

        case 2:

            Descriptor->Memory32.Maximum = (UINT32) InitializerOp->Asl.Value.Integer;
            RsCreateDwordField (InitializerOp, ACPI_RESTAG_MAXADDR,
                CurrentByteOffset + ASL_RESDESC_OFFSET (Memory32.Maximum));
            MaxOp = InitializerOp;
            break;

        case 3:

            Descriptor->Memory32.Alignment = (UINT32) InitializerOp->Asl.Value.Integer;
            RsCreateDwordField (InitializerOp, ACPI_RESTAG_ALIGNMENT,
                CurrentByteOffset + ASL_RESDESC_OFFSET (Memory32.Alignment));
            AlignOp = InitializerOp;
            break;

        case 4:

            Descriptor->Memory32.AddressLength = (UINT32) InitializerOp->Asl.Value.Integer;
            RsCreateDwordField (InitializerOp, ACPI_RESTAG_LENGTH,
                CurrentByteOffset + ASL_RESDESC_OFFSET (Memory32.AddressLength));
            LengthOp = InitializerOp;
            break;

        case 5:

            UtAttachNamepathToOwner (Op, InitializerOp);
            break;

        default:

            AslError (ASL_ERROR, ASL_MSG_RESOURCE_LIST, InitializerOp, NULL);
            break;
        }

        InitializerOp = RsCompleteNodeAndGetNext (InitializerOp);
    }


    RsSmallAddressCheck (ACPI_RESOURCE_NAME_MEMORY32,
        Descriptor->Memory32.Minimum,
        Descriptor->Memory32.Maximum,
        Descriptor->Memory32.AddressLength,
        Descriptor->Memory32.Alignment,
        MinOp, MaxOp, LengthOp, AlignOp, Op);

    return (Rnode);
}
