H5FD_multi_read(H5FD_t *_file, H5FD_mem_t type, hid_t dxpl_id, haddr_t addr, size_t size,
		 void *_buf)
{
    H5FD_multi_t	*file = (H5FD_multi_t*)_file;
    H5FD_multi_dxpl_t	*dx=NULL;
    H5FD_mem_t		mt, mmt, hi=H5FD_MEM_DEFAULT;
    haddr_t		start_addr=0;


    H5Eclear2(H5E_DEFAULT);


    if(H5P_FILE_ACCESS_DEFAULT != dxpl_id && H5FD_MULTI == H5Pget_driver(dxpl_id))
	dx = (H5FD_multi_dxpl_t *)H5Pget_driver_info(dxpl_id);


    for(mt = H5FD_MEM_SUPER; mt < H5FD_MEM_NTYPES; mt = (H5FD_mem_t)(mt + 1)) {
	mmt = file->fa.memb_map[mt];
	if(H5FD_MEM_DEFAULT == mmt)
            mmt = mt;
	assert(mmt > 0 && mmt < H5FD_MEM_NTYPES);

	if (file->fa.memb_addr[mmt]>addr) continue;
	if (file->fa.memb_addr[mmt]>=start_addr) {
	    start_addr = file->fa.memb_addr[mmt];
	    hi = mmt;
	}
    }
    assert(hi>0);


    return H5FDread(file->memb[hi], type, dx?dx->memb_dxpl[hi]:H5P_DEFAULT,
		    addr-start_addr, size, _buf);
}
