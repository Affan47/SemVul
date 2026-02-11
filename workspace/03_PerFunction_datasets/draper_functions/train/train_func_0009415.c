sb_file_put_contents(const char *path, const char* contents, ssize_t len,
    sb_error_t **err)
{
    if (path == NULL || contents == NULL || len == 0)
        return;

    if (err != NULL && *err != NULL)
        return;

    FILE *fp = fopen(path, "w");
    int tmp_errno = errno;

    if (fp == NULL) {
        if (err != NULL)
            *err = sb_error_new_printf(SB_ERROR_FILE_OPEN,
                "Failed to open file (%s): %s", path, strerror(tmp_errno));
        return;
    }


    if (len < 0)
        len = strlen(contents);
    size_t written_len = fwrite(contents, sizeof(char), len, fp);
    tmp_errno = errno;

    if (ferror(fp)) {
        if (err != NULL)
            *err = sb_error_new_printf(SB_ERROR_FILE_WRITE,
                "Failed to write to file (%s): %s", path, strerror(tmp_errno));
        fclose(fp);
        return;
    }

    fclose(fp);

    if (written_len != len && err != NULL)
        *err = sb_error_new_printf(SB_ERROR_FILE_WRITE,
            "Failed to write to file (%s): only %zu bytes written, from %zu",
            written_len, len);
}
