H5HF_sect_single_dblock_info(H5HF_hdr_t *hdr, hid_t dxpl_id,
    H5HF_free_section_t *sect, haddr_t *dblock_addr, size_t *dblock_size)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI(H5HF_sect_single_dblock_info, FAIL)


    HDassert(hdr);
    HDassert(sect);
    HDassert(sect->sect_info.type == H5HF_FSPACE_SECT_SINGLE);
    HDassert(sect->sect_info.state == H5FS_SECT_LIVE);
    HDassert(dblock_addr);
    HDassert(dblock_size);


    if(sect->sect_info.addr < hdr->man_dtable.cparam.start_block_size) {


        if(sect->u.single.parent) {

            if(hdr->man_dtable.curr_root_rows == 0) {

                if(H5HF_iblock_decr(sect->u.single.parent) < 0)
                    HGOTO_ERROR(H5E_HEAP, H5E_CANTDEC, FAIL, "can't decrement reference count on section's indirect block")


                sect->u.single.parent = NULL;
                sect->u.single.par_entry = 0;
            }
            else {


                if(H5HF_sect_single_locate_parent(hdr, dxpl_id, TRUE, sect) < 0)
                    HGOTO_ERROR(H5E_HEAP, H5E_CANTGET, FAIL, "can't get section's parent info")
            }
        }
        else {

            if(hdr->man_dtable.curr_root_rows != 0) {

                if(H5HF_sect_single_locate_parent(hdr, dxpl_id, FALSE, sect) < 0)
                    HGOTO_ERROR(H5E_HEAP, H5E_CANTGET, FAIL, "can't get section's parent info")
            }
        }
    }


    if(hdr->man_dtable.curr_root_rows == 0) {

        HDassert(H5F_addr_defined(hdr->man_dtable.table_addr));
        *dblock_addr =  hdr->man_dtable.table_addr;
        *dblock_size =  hdr->man_dtable.cparam.start_block_size;
    }
    else {

        *dblock_addr =  sect->u.single.parent->ents[sect->u.single.par_entry].addr;
        *dblock_size =  hdr->man_dtable.row_block_size[sect->u.single.par_entry / hdr->man_dtable.cparam.width];
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
