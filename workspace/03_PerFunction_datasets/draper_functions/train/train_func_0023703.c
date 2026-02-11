slotForUserAddress(void * address)
{
	register Slot *	slot = allocationList;
	register size_t	count = slotCount;

	for ( ; count > 0; count-- ) {
		if ( slot->userAddress == address )
			return slot;
		slot++;
	}

	return 0;
}
