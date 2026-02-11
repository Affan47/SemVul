cmp_file(char * file, char * dir, char * name) {
    int i;
    if (file == NULL) return 0;
    if (name == NULL) return 0;
    if (strcmp(file, name) == 0) return 1;
    i = strlen(name);
    while (i > 0 && name[i - 1] != '/' && name[i - 1] != '\\') i--;
    if (strcmp(file, name + i) == 0) return 1;
    if (dir == NULL) return 0;
    i = strlen(dir);
    if (strncmp(dir, file, i) == 0 && (file[i] == '/' || file[i] == '\\') &&
            strcmp(file + i + 1, name) == 0) return 1;
    return 0;
}
