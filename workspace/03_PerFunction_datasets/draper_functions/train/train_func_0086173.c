H5FD_core_flush(H5FD_t *_file, hid_t H5_ATTR_UNUSED dxpl_id, unsigned H5_ATTR_UNUSED closing)
{
    H5FD_core_t *file = (H5FD_core_t*)_file;
    herr_t      ret_value = SUCCEED;

    FUNC_ENTER_NOAPI_NOINIT


    if (file->dirty && file->fd >= 0 && file->backing_store) {


        if(file->dirty_list) {
            H5FD_core_region_t *item = NULL;
            size_t size;

#ifdef DER
    fprintf(stderr, "FLUSHING. DIRTY LIST:\n");
#endif
            while(NULL != (item = (H5FD_core_region_t *)H5SL_remove_first(file->dirty_list))) {


                if(item->start < file->eof) {
                    if(item->end >= file->eof)
                        item->end = file->eof - 1;
                    size = (size_t)((item->end - item->start) + 1);
#ifdef DER
fprintf(stderr, "(%llu, %llu : %lu)\n", item->start, item->end, size);
#endif
                    if(H5FD_core_write_to_bstore(file, item->start, size) != SUCCEED)
                        HGOTO_ERROR(H5E_VFL, H5E_WRITEERROR, FAIL, "unable to write to backing store")
                }

                item = H5FL_FREE(H5FD_core_region_t, item);
            }


#ifdef DER
fprintf(stderr, "EOF: %llu\n", file->eof);
fprintf(stderr, "EOA: %llu\n", file->eoa);
if(file->eoa > file->eof)
    fprintf(stderr, "*** EOA BADNESS ***\n");
fprintf(stderr, "\n");
#endif
        }

        else {
            if(H5FD_core_write_to_bstore(file, (haddr_t)0, (size_t)file->eof) != SUCCEED)
                HGOTO_ERROR(H5E_VFL, H5E_WRITEERROR, FAIL, "unable to write to backing store")

        }

        file->dirty = FALSE;
    }

done:
    FUNC_LEAVE_NOAPI(ret_value)
}
