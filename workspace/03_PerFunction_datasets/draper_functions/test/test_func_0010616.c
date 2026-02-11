nway_start(struct nic *nic __unused)
{
    int csr14 = ((tp->sym_advertise & 0x0780) << 9)  |
        ((tp->sym_advertise&0x0020)<<1) | 0xffbf;

#ifdef TULIP_DEBUG_WHERE
    whereami("nway_start\n");
#endif

    tp->if_port = 0;
    tp->nway = tp->mediasense = 1;
    tp->nwayset = tp->lpar = 0;
    if (tp->chip_id == PNIC2) {
        tp->csr6 = 0x01000000 | (tp->sym_advertise & 0x0040 ? 0x0200 : 0);
        return;
    }
#ifdef TULIP_DEBUG
    if (tulip_debug > 1)
        printf("%s: Restarting internal NWay autonegotiation, %X.\n",
               tp->nic_name, csr14);
#endif
    outl(0x0001, ioaddr + CSR13);
    outl(csr14, ioaddr + CSR14);
    tp->csr6 = 0x82420000 | (tp->sym_advertise & 0x0040 ? 0x0200 : 0);
    outl(tp->csr6, ioaddr + CSR6);
    if (tp->mtable  &&  tp->mtable->csr15dir) {
        outl(tp->mtable->csr15dir, ioaddr + CSR15);
        outl(tp->mtable->csr15val, ioaddr + CSR15);
    } else if (tp->chip_id != PNIC2)
        outw(0x0008, ioaddr + CSR15);
    if (tp->chip_id == DC21041)
        outl(0xEF01, ioaddr + CSR12);
    else
        outl(0x1301, ioaddr + CSR12);
}
