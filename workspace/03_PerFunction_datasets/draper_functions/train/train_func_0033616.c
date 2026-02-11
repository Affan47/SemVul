fill_validation_data(struct zc_ctx *ctx, const char *filename,
                            struct zc_validation_data *vdata, size_t nmemb)
{
    struct zc_file *file = NULL;
    int err;

    err = zc_file_new_from_filename(ctx, filename, &file);
    if (!file) {
        yazc_err("zc_file_new_from_filename() failed!\n");
        return 0;
    }

    err = zc_file_open(file);
    if (err) {
        yazc_err("failed to open %s.\n", filename);
        zc_file_unref(file);
        return 0;
    }

    err = zc_file_read_validation_data(file, vdata, nmemb);
    if (err < 1)
        yazc_err("file is not encrypted.\n");

    zc_file_close(file);
    zc_file_unref(file);
    return err < 1 ? 0 : (size_t)err;
}
