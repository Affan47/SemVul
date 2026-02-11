H5HF_sect_single_new(hsize_t sect_off, size_t sect_size,
    H5HF_indirect_t *parent, unsigned par_entry)
{
    H5HF_free_section_t *sect = NULL;
    H5HF_free_section_t *ret_value;

    FUNC_ENTER_NOAPI_NOINIT


    HDassert(sect_size);


    if(NULL == (sect = H5HF_sect_node_new(H5HF_FSPACE_SECT_SINGLE, sect_off, (hsize_t)sect_size, H5FS_SECT_LIVE)))
        HGOTO_ERROR(H5E_RESOURCE, H5E_NOSPACE, NULL, "memory allocation failed for single section")


    sect->u.single.parent = parent;
    if(sect->u.single.parent) {
        if(H5HF_iblock_incr(sect->u.single.parent) < 0)
            HGOTO_ERROR(H5E_HEAP, H5E_CANTINC, NULL, "can't increment reference count on shared indirect block")
    }
    sect->u.single.par_entry = par_entry;


    ret_value = sect;

done:
    if(!ret_value && sect) {

        sect = H5FL_FREE(H5HF_free_section_t, sect);
    }

    FUNC_LEAVE_NOAPI(ret_value)
}
