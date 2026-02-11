AcpiTbInitGenericAddress (
    ACPI_GENERIC_ADDRESS    *GenericAddress,
    UINT8                   SpaceId,
    UINT8                   ByteWidth,
    UINT64                  Address,
    char                    *RegisterName)
{
    UINT8                   BitWidth;


    BitWidth = (UINT8) (ByteWidth * 8);

    if (ByteWidth > 31)
    {
        ACPI_ERROR ((AE_INFO,
            "%s - 32-bit FADT register is too long (%u bytes, %u bits) "
            "to convert to GAS struct - 255 bits max, truncating",
            RegisterName, ByteWidth, (ByteWidth * 8)));

        BitWidth = 255;
    }


    ACPI_MOVE_64_TO_64 (&GenericAddress->Address, &Address);


    GenericAddress->SpaceId = SpaceId;
    GenericAddress->BitWidth = BitWidth;
    GenericAddress->BitOffset = 0;
    GenericAddress->AccessWidth = 0;
}
