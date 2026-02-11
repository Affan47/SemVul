H5FDset_eoa(H5FD_t *file, H5FD_mem_t type, haddr_t addr)
{
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_API(FAIL)
    H5TRACE3("e", "*xMta", file, type, addr);


    if(!file || !file->cls)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid file pointer")
    if(type < H5FD_MEM_DEFAULT || type >= H5FD_MEM_NTYPES)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid file type")
    if(!H5F_addr_defined(addr) || addr > file->maxaddr)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, FAIL, "invalid end-of-address value")


    if(H5FD_set_eoa(file, type, addr - file->base_addr) < 0)
	HGOTO_ERROR(H5E_VFL, H5E_CANTINIT, FAIL, "file set eoa request failed")

done:
    FUNC_LEAVE_API(ret_value)
}
