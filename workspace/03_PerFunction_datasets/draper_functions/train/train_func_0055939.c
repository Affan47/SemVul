H5FS_sect_decrease(H5FS_t *fspace, const H5FS_section_class_t *cls)
{
    herr_t ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT(H5FS_sect_decrease)


    HDassert(fspace);
    HDassert(fspace->sinfo);
    HDassert(cls);


    fspace->tot_sect_count--;


    if(cls->flags & H5FS_CLS_GHOST_OBJ) {

        HDassert(cls->serial_size == 0);


        fspace->ghost_sect_count--;
    }
    else {

        fspace->serial_sect_count--;


#ifdef QAK
HDfprintf(stderr, "%s: fspace->serial_size = %Zu\n", FUNC, fspace->sinfo->serial_size);
HDfprintf(stderr, "%s: cls->serial_size = %Zu\n", FUNC, cls->serial_size);
#endif
        fspace->sinfo->serial_size -= cls->serial_size;


        if(H5FS_sect_serialize_size(fspace) < 0)
            HGOTO_ERROR(H5E_FSPACE, H5E_CANTCOMPUTE, FAIL, "can't adjust free space section size on disk")
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
