RsDoIrqDescriptor (
    ACPI_PARSE_OBJECT       *Op,
    UINT32                  CurrentByteOffset)
{
    AML_RESOURCE            *Descriptor;
    ACPI_PARSE_OBJECT       *InitializerOp;
    ASL_RESOURCE_NODE       *Rnode;
    UINT32                  Interrupts = 0;
    UINT16                  IrqMask = 0;
    UINT32                  i;


    InitializerOp = Op->Asl.Child;
    Rnode = RsAllocateResourceNode (sizeof (AML_RESOURCE_IRQ));


    Descriptor = Rnode->Buffer;
    Descriptor->Irq.DescriptorType  = ACPI_RESOURCE_NAME_IRQ |
                                      (ASL_RDESC_IRQ_SIZE + 0x01);


    for (i = 0; InitializerOp; i++)
    {
        switch (i)
        {
        case 0:

            RsSetFlagBits (&Descriptor->Irq.Flags, InitializerOp, 0, 1);
            RsCreateBitField (InitializerOp, ACPI_RESTAG_INTERRUPTTYPE,
                CurrentByteOffset + ASL_RESDESC_OFFSET (Irq.Flags), 0);
            break;

        case 1:

            RsSetFlagBits (&Descriptor->Irq.Flags, InitializerOp, 3, 0);
            RsCreateBitField (InitializerOp, ACPI_RESTAG_INTERRUPTLEVEL,
                CurrentByteOffset + ASL_RESDESC_OFFSET (Irq.Flags), 3);
            break;

        case 2:

            RsSetFlagBits (&Descriptor->Irq.Flags, InitializerOp, 4, 0);
            RsCreateBitField (InitializerOp, ACPI_RESTAG_INTERRUPTSHARE,
                CurrentByteOffset + ASL_RESDESC_OFFSET (Irq.Flags), 4);
            break;

        case 3:

            UtAttachNamepathToOwner (Op, InitializerOp);
            break;

        default:


            if (InitializerOp->Asl.ParseOpcode != PARSEOP_DEFAULT_ARG)
            {


                Interrupts++;
                if (Interrupts > 16)
                {
                    AslError (ASL_ERROR, ASL_MSG_INTERRUPT_LIST,
                        InitializerOp, NULL);
                    return (Rnode);
                }


                if (InitializerOp->Asl.Value.Integer > 15)
                {
                    AslError (ASL_ERROR, ASL_MSG_INTERRUPT_NUMBER,
                        InitializerOp, NULL);
                }
                else
                {
                    IrqMask |= (1 << (UINT8) InitializerOp->Asl.Value.Integer);
                }
            }


            if (i == 4)
            {


                RsCheckListForDuplicates (InitializerOp);


                RsCreateWordField (InitializerOp, ACPI_RESTAG_INTERRUPT,
                    CurrentByteOffset + ASL_RESDESC_OFFSET (Irq.IrqMask));
            }
            break;
        }

        InitializerOp = RsCompleteNodeAndGetNext (InitializerOp);
    }


    ACPI_MOVE_16_TO_16(&Descriptor->Irq.IrqMask, &IrqMask);
    return (Rnode);
}
