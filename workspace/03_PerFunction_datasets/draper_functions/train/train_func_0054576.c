realloc(void * oldBuffer, size_t newSize)
{
	void *	newBuffer = 0;

	if ( allocationList == 0 )
		initialize();

        lock();

	newBuffer = memalign_locked(EF_ALIGNMENT, newSize);

	if ( oldBuffer ) {
		size_t	size;
		Slot *	slot;

		Page_AllowAccess(allocationList, allocationListSize);
		noAllocationListProtection = 1;

		slot = slotForUserAddress(oldBuffer);

		if ( slot == 0 )
			EF_Abort(
			 "realloc(%a, %d): address not from malloc()."
			,oldBuffer
			,newSize);

		if ( newSize < (size = slot->userSize) )
			size = newSize;

		if ( size > 0 )
			memcpy(newBuffer, oldBuffer, size);

		free_locked(oldBuffer);
		noAllocationListProtection = 0;
		Page_DenyAccess(allocationList, allocationListSize);

		if ( size < newSize )
			memset(&(((char *)newBuffer)[size]), 0, newSize - size);


	}
	release();

	return newBuffer;
}
