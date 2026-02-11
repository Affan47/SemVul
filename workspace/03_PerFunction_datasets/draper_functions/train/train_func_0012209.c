multi_xfer_xor_flags(int handle,int flags)
{

	if(MULTI_XFER_INVALID_HANDLE(handle)){
		return;
	}


	Multi_xfer_entry[handle].flags ^= flags;
}
