note_file_seek(VMG_ vm_obj_id_t self, int is_explicit)
{


    if (is_explicit)
    {

        if (get_ext()->readbuf != 0)
            get_ext()->readbuf->rem = 0;


        get_ext()->flags &= ~VMOBJFILE_STDIO_BUF_DIRTY;
    }
}
