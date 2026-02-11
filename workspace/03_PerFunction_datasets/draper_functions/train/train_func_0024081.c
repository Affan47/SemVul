xps_close_device(gx_device *dev)
{
    gx_device_xps *const xps = (gx_device_xps*)dev;
    int code;


    code = write_str_to_zip_file(xps, "Documents/1/FixedDocument.fdoc", "</FixedDocument>");
    if (code < 0)
        return gs_rethrow_code(code);

    if (ferror(xps->file))
      return gs_throw_code(gs_error_ioerror);

    code = zip_close_archive(xps);
    if (code < 0)
        return gs_rethrow_code(code);

    return gdev_vector_close_file((gx_device_vector*)dev);
}
