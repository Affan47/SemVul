png_save_to_callback_write_func (png_structp png_ptr,
                                 png_bytep   data,
                                 png_size_t  length)
{
        SaveToFunctionIoPtr *ioptr = png_get_io_ptr (png_ptr);

        if (!ioptr->save_func ((gchar *)data, length, ioptr->error, ioptr->user_data)) {


                png_error (png_ptr, "write function failed");
        }
}
