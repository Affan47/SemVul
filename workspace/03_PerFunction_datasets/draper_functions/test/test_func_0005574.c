RsDoFixedDmaDescriptor (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  CurrentByteOffset)
{
    AML_RESOURCE            *Descriptor;
    ACPI_PARSE_OBJECT       *InitializerOp;
    ASL_RESOURCE_NODE       *Rnode;
    UINT16                  RequestLines = 0;
    UINT16                  Channels = 0;
    UINT32                  i;


    InitializerOp = Op->Asl.Child;
    Rnode = RsAllocateResourceNode (sizeof (AML_RESOURCE_FIXED_DMA));

    Descriptor = Rnode->Buffer;
    Descriptor->FixedDma.DescriptorType =
        ACPI_RESOURCE_NAME_FIXED_DMA | ASL_RDESC_FIXED_DMA_SIZE;


    for (i = 0; InitializerOp; i++)
    {
        switch (i)
        {
        case 0:

            RequestLines = (UINT16) InitializerOp->Asl.Value.Integer;
            RsCreateWordField (InitializerOp, ACPI_RESTAG_DMA,
                CurrentByteOffset + ASL_RESDESC_OFFSET (FixedDma.RequestLines));
            break;

        case 1:

            Channels = (UINT16) InitializerOp->Asl.Value.Integer;
            RsCreateWordField (InitializerOp, ACPI_RESTAG_DMATYPE,
                CurrentByteOffset + ASL_RESDESC_OFFSET (FixedDma.Channels));
            break;

        case 2:

            Descriptor->FixedDma.Width = (UINT8) InitializerOp->Asl.Value.Integer;
            RsCreateByteField (InitializerOp, ACPI_RESTAG_XFERTYPE,
                CurrentByteOffset + ASL_RESDESC_OFFSET (FixedDma.Width));
            break;

        case 3:

            UtAttachNamepathToOwner (Op, InitializerOp);
            break;

        default:

            break;
        }

        InitializerOp = RsCompleteNodeAndGetNext (InitializerOp);
    }

    ACPI_MOVE_16_TO_16(&Descriptor->FixedDma.RequestLines, &RequestLines);
    ACPI_MOVE_16_TO_16(&Descriptor->FixedDma.Channels, &Channels);

    return (Rnode);
}
