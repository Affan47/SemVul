fore200e_get_esi(struct fore200e *fore200e)
{
    struct prom_data* prom = kzalloc(sizeof(struct prom_data), GFP_KERNEL | GFP_DMA);
    int ok, i;

    if (!prom)
	return -ENOMEM;

    ok = fore200e->bus->prom_read(fore200e, prom);
    if (ok < 0) {
	kfree(prom);
	return -EBUSY;
    }

    printk(FORE200E "device %s, rev. %c, S/N: %d, ESI: %pM\n",
	   fore200e->name,
	   (prom->hw_revision & 0xFF) + '@',
	   prom->serial_number & 0xFFFF, &prom->mac_addr[2]);

    for (i = 0; i < ESI_LEN; i++) {
	fore200e->esi[ i ] = fore200e->atm_dev->esi[ i ] = prom->mac_addr[ i + 2 ];
    }

    kfree(prom);

    return 0;
}
