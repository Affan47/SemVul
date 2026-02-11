H5FDget_eoa(H5FD_t *file, H5FD_mem_t type)
{
    haddr_t	ret_value;

    FUNC_ENTER_API(HADDR_UNDEF)
    H5TRACE2("a", "*xMt", file, type);


    if(!file || !file->cls)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, HADDR_UNDEF, "invalid file pointer")
    if(type < H5FD_MEM_DEFAULT || type >= H5FD_MEM_NTYPES)
	HGOTO_ERROR(H5E_ARGS, H5E_BADVALUE, HADDR_UNDEF, "invalid file type")


    if(HADDR_UNDEF == (ret_value = H5FD_get_eoa(file, type)))
	HGOTO_ERROR(H5E_VFL, H5E_CANTINIT, HADDR_UNDEF, "file get eoa request failed")


    ret_value += file->base_addr;

done:
    FUNC_LEAVE_API(ret_value)
}
