volume_set_fs_type(volume_t *volume, const char *fsType) {

    if (volume != NULL) {
        free(volume->fsType);
        fsType = volume->fsType = strdup(fsType);
    }
    else fsType = NULL;

    return fsType;
}
