libbdplus_required(const char *device_path)
{
    BD_FILE_H *fd;
    char      *tmp;

    tmp = str_printf("%s/BDSVM/00000.svm", device_path);
    fd = file_open(tmp, "rb");
    X_FREE(tmp);

    if (fd) {
        file_close(fd);

        BD_DEBUG(DBG_BLURAY, "BDSVM/00000.svm found. Disc seems to be BD+ protected.\n");
        return 1;
    }

    BD_DEBUG(DBG_BLURAY, "BDSVM/00000.svm not found. No BD+ protection.\n");
    return 0;
}
