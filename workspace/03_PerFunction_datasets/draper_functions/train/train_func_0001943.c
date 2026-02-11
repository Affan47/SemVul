sis900_mdio_reset(long mdio_addr)
{
    int i;

    for (i = 31; i >= 0; i--) {
        outl(MDDIR | MDIO, mdio_addr);
        sis900_mdio_delay();
        outl(MDDIR | MDIO | MDC, mdio_addr);
        sis900_mdio_delay();
    }
    return;
}
