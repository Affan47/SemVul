tulip_transmit(struct nic *nic, const char *d, unsigned int t,
                           unsigned int s, const char *p)
{
    u16 nstype;
    u32 to;
    u32 csr6 = inl(ioaddr + CSR6);

    whereami("tulip_transmit\n");


    outl(csr6 & ~0x00002000, ioaddr + CSR6);

    memcpy(txb, d, ETH_ALEN);
    memcpy(txb + ETH_ALEN, nic->node_addr, ETH_ALEN);
    nstype = htons((u16) t);
    memcpy(txb + 2 * ETH_ALEN, (u8 *)&nstype, 2);
    memcpy(txb + ETH_HLEN, p, s);

    s += ETH_HLEN;
    s &= 0x0FFF;


    while (s < ETH_ZLEN)
        txb[s++] = '\0';

    DBG2("%s: sending %d bytes ethtype %hX\n", tp->nic_name, s, t);


    tx_ring[0].length = cpu_to_le32(0x60000000 | s);
    tx_ring[0].status = cpu_to_le32(0x80000000);


    outl(virt_to_le32desc(&tx_ring[0]), ioaddr + CSR4);


    outl(csr6 | 0x00002000, ioaddr + CSR6);

    outl(0, ioaddr + CSR1);

    to = currticks() + TX_TIME_OUT;
    while ((tx_ring[0].status & 0x80000000) && (currticks() < to))
         ;

    if (currticks() >= to) {
        DBG ("TX Timeout!\n");
    }


    outl(csr6 & ~0x00002000, ioaddr + CSR6);
}
