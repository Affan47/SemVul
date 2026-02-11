RsDoFixedIoDescriptor (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  CurrentByteOffset)
{
    AML_RESOURCE            *Descriptor;
    ACPI_PARSE_OBJECT       *InitializerOp;
    ACPI_PARSE_OBJECT       *AddressOp = NULL;
    ASL_RESOURCE_NODE       *Rnode;
    UINT16                  Address = 0;
    UINT32                  i;


    InitializerOp = Op->Asl.Child;
    Rnode = RsAllocateResourceNode (sizeof (AML_RESOURCE_FIXED_IO));

    Descriptor = Rnode->Buffer;
    Descriptor->Io.DescriptorType  = ACPI_RESOURCE_NAME_FIXED_IO |
                                      ASL_RDESC_FIXED_IO_SIZE;


    for (i = 0; InitializerOp; i++)
    {
        switch (i)
        {
        case 0:

            Address = (UINT16) InitializerOp->Asl.Value.Integer;
            RsCreateWordField (InitializerOp, ACPI_RESTAG_BASEADDRESS,
                CurrentByteOffset + ASL_RESDESC_OFFSET (FixedIo.Address));
            AddressOp = InitializerOp;
            break;

        case 1:

            Descriptor->FixedIo.AddressLength =
                (UINT8) InitializerOp->Asl.Value.Integer;
            RsCreateByteField (InitializerOp, ACPI_RESTAG_LENGTH,
                CurrentByteOffset + ASL_RESDESC_OFFSET (FixedIo.AddressLength));
            break;

        case 2:

            UtAttachNamepathToOwner (Op, InitializerOp);
            break;

        default:

            AslError (ASL_ERROR, ASL_MSG_RESOURCE_LIST, InitializerOp, NULL);
            break;
        }

        InitializerOp = RsCompleteNodeAndGetNext (InitializerOp);
    }


    if (Address > 0x03FF)
    {
        AslError (ASL_WARNING, ASL_MSG_ISA_ADDRESS, AddressOp, NULL);
    }

    ACPI_MOVE_16_TO_16(&Descriptor->FixedIo.Address, &Address);

    return (Rnode);
}
