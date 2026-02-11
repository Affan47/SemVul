is_driftnet_file(char *filename) {
    if (strncmp(filename, "driftnet-", 9) != 0) return 0;
    char *p = strrchr(filename, '.');
    if (p == 0) return 0;
    return (strcmp(p, ".jpeg") == 0 ||
           strcmp(p, ".gif") == 0 ||
           strcmp(p, ".png") == 0 ||
           strcmp(p, ".mp3") == 0);
}
