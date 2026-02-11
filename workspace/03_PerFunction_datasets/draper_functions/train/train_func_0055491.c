hdf_term_destination(struct jpeg_compress_struct *cinfo_ptr)
{
    hdf_dest_ptr dest=(hdf_dest_ptr)cinfo_ptr->dest;

    int32 datacount = (int32)OUTPUT_BUF_SIZE - (int32)dest->pub.free_in_buffer;


    if (datacount > 0) {
        if (Hwrite(dest->aid, datacount, dest->buffer) != datacount)
            ERREXIT(cinfo_ptr, JERR_FILE_WRITE);
    }


    Hendaccess(dest->aid);


    HDfree(dest->buffer);

}
