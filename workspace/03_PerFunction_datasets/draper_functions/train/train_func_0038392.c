multi_xfer_reset()
{
	int idx;


	for(idx=0;idx<MAX_XFER_ENTRIES;idx++){
		if(Multi_xfer_entry[idx].flags & MULTI_XFER_FLAG_USED){
			multi_xfer_abort(idx);
		}
	}


	memset(Multi_xfer_entry,0,sizeof(xfer_entry) * MAX_XFER_ENTRIES);
}
