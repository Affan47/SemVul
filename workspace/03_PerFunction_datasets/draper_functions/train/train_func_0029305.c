AcpiDmGetResourceTag (
    UINT32                  BitIndex,
    AML_RESOURCE            *Resource,
    UINT8                   ResourceIndex)
{
    const ACPI_RESOURCE_TAG *TagList;
    char                    *Tag = NULL;


    TagList = AcpiGbl_ResourceTags[ResourceIndex];


    switch (Resource->DescriptorType)
    {
    case ACPI_RESOURCE_NAME_ADDRESS16:
    case ACPI_RESOURCE_NAME_ADDRESS32:
    case ACPI_RESOURCE_NAME_ADDRESS64:
    case ACPI_RESOURCE_NAME_EXTENDED_ADDRESS64:


        if (Resource->Address.ResourceType == ACPI_ADDRESS_TYPE_MEMORY_RANGE)
        {
            Tag = AcpiDmSearchTagList (BitIndex, AcpiDmMemoryFlagTags);
        }
        else if (Resource->Address.ResourceType == ACPI_ADDRESS_TYPE_IO_RANGE)
        {
            Tag = AcpiDmSearchTagList (BitIndex, AcpiDmIoFlagTags);
        }


        if (Tag)
        {
            return (Tag);
        }
        break;

    case ACPI_RESOURCE_NAME_GPIO:


        if (Resource->Gpio.ConnectionType > AML_RESOURCE_MAX_GPIOTYPE)
        {
            return (NULL);
        }

        TagList = AcpiGbl_GpioResourceTags[Resource->Gpio.ConnectionType];
        break;

    case ACPI_RESOURCE_NAME_SERIAL_BUS:


        if ((Resource->CommonSerialBus.Type == 0) ||
            (Resource->CommonSerialBus.Type > AML_RESOURCE_MAX_SERIALBUSTYPE))
        {
            return (NULL);
        }

        TagList = AcpiGbl_SerialResourceTags[Resource->CommonSerialBus.Type];
        break;

    default:

        break;
    }


    if (TagList)
    {
        Tag = AcpiDmSearchTagList (BitIndex, TagList);
    }

    return (Tag);
}
