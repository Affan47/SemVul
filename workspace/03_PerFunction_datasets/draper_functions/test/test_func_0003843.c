lkbde_get_dev_phys_hi(int d)
{
    if (!VALID_DEVICE(d)) {
        return -1;
    }

    if (!(BDE_DEV_MEM_MAPPED(_devices[d].dev_type))) {
        gprintk("lkbde_get_dev_phys: Not PCI device %d, type %x\n",
                d, _devices[d].dev_type);
        return 0;
    }
#ifdef PHYS_ADDR_IS_64BIT
    return (uint32_t)(_devices[d].phys_address >> 32);
#else
    return 0;
#endif
}
