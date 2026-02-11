memorySpace(unsigned long *addr)
{
    int mask;


    if (*addr & DATA_SPACE_ADDR_OFFSET)
    {
	mask = *addr & ADDR_SPACE_MASK;
	*addr &= ~ADDR_SPACE_MASK;
    }
    else
	mask = 0;

    switch (mask)
    {
    case  EEPROM_SPACE_ADDR_OFFSET: return ADDR_EEPROM_SPACE;
    case FUSE_SPACE_ADDR_OFFSET: return ADDR_FUSE_SPACE;
    case LOCK_SPACE_ADDR_OFFSET: return ADDR_LOCK_SPACE;
    case SIG_SPACE_ADDR_OFFSET: return ADDR_SIG_SPACE;
    case BREAKPOINT_SPACE_ADDR_OFFSET: return ADDR_BREAKPOINT_SPACE;
    case DATA_SPACE_ADDR_OFFSET: return ADDR_DATA_SPACE;
    default: return 0;
    }
}
