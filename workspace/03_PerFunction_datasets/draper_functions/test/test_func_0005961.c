fstab_parse(const char *path, volume_list_t *list) {

    FILE *fstab;
    char buf[1024];
    int i, result;
    char *spec, *mountPoint, *fsType, *mountOptions, *freq, *passno;
    volume_t *volume;


    fstab = fopen(path, "r");
    if (fstab != NULL) {

        while (fgets(buf, sizeof(buf)-1, fstab)) {

            for (i = 0; (buf[i] != '\0') && (isspace(buf[i])); i++);


            if ((buf[i] == '\0') || (buf[i] == '#')) continue;


            spec         = strtok(buf+i, " \t");
            mountPoint   = strtok(NULL, " \t");
            fsType       = strtok(NULL, " \t");
            mountOptions = strtok(NULL, " \t");
            freq         = strtok(NULL, " \t");
            passno       = strtok(NULL, " \t");


            mountOptions = mountOptions;
            freq         = freq;
            passno       = passno;


            volume = volume_new();
            if (volume != NULL) {
                volume_set_spec(volume, spec);
                volume_set_mount_point(volume, mountPoint);
                volume_set_fs_type(volume, fsType);

                volume_list_add(list, volume);
            }
        }
        fclose(fstab);
        result = 0;
    }
    else result = ENOENT;

    return result;
}
