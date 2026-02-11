check_params(const SDFile *sdfile,
             guint len,
             GError **error)
{
    if (sdfile->data_type >= SDF_NTYPES) {
        err_DATA_TYPE(error, sdfile->data_type);
        return FALSE;
    }
    if (err_DIMENSION(error, sdfile->xres)
        || err_DIMENSION(error, sdfile->yres))
        return FALSE;
    if (err_SIZE_MISMATCH(error, sdfile->expected_size, len, FALSE))
        return FALSE;
    if (sdfile->compression) {
        err_UNSUPPORTED(error, "Compression");
        return FALSE;
    }
    if (sdfile->check_type) {
        err_UNSUPPORTED(error, "CheckType");
        return FALSE;
    }

    return TRUE;
}
