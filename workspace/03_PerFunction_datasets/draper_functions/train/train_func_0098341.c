H5HF_dblock_debug_cb(const H5FS_section_info_t *_sect, void *_udata)
{
    const H5HF_free_section_t *sect = (const H5HF_free_section_t *)_sect;
    H5HF_debug_iter_ud1_t *udata = (H5HF_debug_iter_ud1_t *)_udata;
    haddr_t sect_start, sect_end;
    haddr_t dblock_start, dblock_end;

    FUNC_ENTER_NOAPI_NOINIT_NOFUNC(H5HF_dblock_debug_cb)


    HDassert(sect);
    HDassert(udata);


    sect_start = sect->sect_info.addr;
    sect_end = (sect->sect_info.addr + sect->sect_info.size) - 1;
    HDassert(sect_end >= sect_start);
    dblock_start = udata->dblock_addr;
    dblock_end = (udata->dblock_addr + udata->dblock_size) - 1;
    HDassert(dblock_end >= dblock_start);


    if((sect_start <= dblock_end && sect_end >=dblock_start) ||
            (sect_start <= dblock_end && sect_end >=dblock_end)) {
        char temp_str[32];
        size_t start, end;
        size_t len;
        size_t overlap;
        unsigned u;


        if(sect_start < dblock_start)
            start = 0;
        else
            H5_ASSIGN_OVERFLOW( start,  (sect_start - dblock_start),  hsize_t,  size_t)
        if(sect_end > dblock_end)
            H5_ASSIGN_OVERFLOW( end,  udata->dblock_size,  hsize_t,  size_t)
        else
            H5_ASSIGN_OVERFLOW( end,  ((sect_end - dblock_start) + 1),  hsize_t,  size_t)


        len = end - start;

        sprintf(temp_str, "Section #%u:", (unsigned)udata->sect_count);
	HDfprintf(udata->stream, "%*s%-*s %8Zu, %8Zu\n", udata->indent + 3, "", MAX(0, udata->fwidth - 9),
		temp_str,
		start, len);
        udata->sect_count++;


        overlap = 0;
        for(u = start; u < end; u++) {
            if(udata->marker[u])
                overlap++;
            udata->marker[u] = 1;
        }


        if (overlap)
            fprintf(udata->stream, "***THAT FREE BLOCK OVERLAPPED A PREVIOUS ONE!\n");
        else
            udata->amount_free += len;
    }

    FUNC_LEAVE_NOAPI(SUCCEED)
}
