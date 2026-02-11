check_psi_ext(char *file)
{
    char *ext;

    if (strlen(file) < 5) {
        return 0;
    }

    ext = strrchr(file, '.');

    if ((ext == NULL) || (strlen(ext) != 4)) {
        return 0;
    }

    if (strcmp(ext, ".psi") == 0) {
        return 1;
    } else {
        return 0;
    }
}
