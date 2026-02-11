initvblankABI (uaecptr base, uaecptr ABI)
{
    for (int i = 0; i < 22; i++)
        put_byte (ABI + PSSO_BoardInfo_HardInterrupt + i, get_byte (base + CARD_PORTSIRQ + i));
    ABI_interrupt = ABI;
}
